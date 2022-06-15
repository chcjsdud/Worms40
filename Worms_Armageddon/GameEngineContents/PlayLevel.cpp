#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "Player.h"
#include "WeaponMaster.h"
#include "Inventory.h"
#include "Cursor.h"
#include "MapBooks.h"
#include "TeamHpBarList.h"
#include "GameOptions.h"
#include "TimerActor.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngine.h>

#include <string>
#include "AirBomb.h"

PlayLevel::PlayLevel()
	: LevelPhase_(LevelFSM::Ready)
	, LerpTimer_(0.0f)
	, PrevPlayerPos_(float4::ZERO)
	, NextPlayerPos_(float4::ZERO)
	, LerpStartCameraPos_(float4::ZERO)
	, CurrentWeaponPos_(float4::ZERO)
	, CameraControledByWASDFlg_(false)
	, PlayShootingStar_(nullptr)
	, DamagedCharCameraDelayTimer_(nullptr)
	, GameMapInfo_(nullptr)
	, InventoryActor_(nullptr)
	, Mouse_ (nullptr)
	, PrevPhase_(LevelFSM::Ready)
	, TargetPlayer_(nullptr)
	, TeamHpBarListActor_(nullptr)
	, WeaponMaster_(nullptr)
	, WindGaugeActor_(nullptr)
	, WindSpeed_(0.f)
{
	// 플레이어 배열 초기화
	for (int TeamColor = 0; TeamColor < PLAYER_MAX_TEAM; TeamColor++)
	{
		for (int PlayerNum = 0; PlayerNum < PLAYER_MAX_NUMBER; PlayerNum++)
		{
			Player_[TeamColor][PlayerNum] = nullptr;
		}
	}
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{
	// 테스트용 코드, 맵 선택에 따라서 다른 액터 생성
	//배경화면 액터
	GameMapInfo_ = CreateActor<MapBooks>();
	// 카메라 딜레이용 타이머 액터
	DamagedCharCameraDelayTimer_ = CreateActor<TimerActor>();

	// 마우스
	Mouse_ = CreateActor<Cursor>((int)ActorGroup::UI);
	// 바람 게이지
	WindGaugeActor_ = CreateActor<WindGauge>((int)RenderOrder::UI);
	WindGaugeActor_->SetPosition({ 1180.0f, 940.0f });
	// 인벤토리
	InventoryActor_ = CreateActor<Inventory>((int)ActorGroup::UI);
	// 팀 HP바
	TeamHpBarListActor_ = CreateActor<TeamHpBarList>((int)ActorGroup::UI);

	// 무기 설정
	WeaponMaster_ = CreateActor<WeaponMaster>();
	WeaponMaster_->SetGameMap(GameMapInfo_);

	//별떨어지기
	PlayShootingStar_ = CreateActor<PlayShootingStar>(static_cast<int>(ActorGroup::UI));

	// 테스트용 코드 끝
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOUSE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_LEFT, VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_RIGHT, VK_RBUTTON);
	}

	//WindSpeed_ = 45.0f;
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress(KEY_CHANGE_CREDITLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_CREDIT_LEVEL);
	}

	// 에어스트라크
	PlayerDamagedCheck4AirStrike();
	// 일반무기에 대한
	PlayerDamagedCheck4NormalWeapon();

	for (std::list<Player*>& Team : AllPlayer_)
	{
		for (Player* Player : Team)
		{
			Player->SetControlFlg(false);
			//Player->SetTurnEndFlg(false);
		}
	}

	switch (LevelPhase_)
	{
	case LevelFSM::Ready:

		// CurrentTeam.size() == 0

		for (std::list<Player*>& Team : AllPlayer_)
		{
			PlayQueue_.push_back(std::list<Player*>());

			for (Player* Player : Team)
			{
				if (Player->GetIsDeath())
				{
					continue;
				}

				PlayQueue_.back().push_back(Player);
			}
		}

		AllPlayerIter_ = PlayQueue_.begin();

		// 조작 가능한 플레이어가 모두 없어졌을 경우 크레딧 레벨로
		if (AllPlayerIter_->size() == 0)
		{
			// 2초 대기
			Sleep(2000);

			GameEngine::GetInst().ChangeLevel(LEVEL_CREDIT_LEVEL);

			return;
		}

		TargetPlayer_ = *AllPlayerIter_->begin();

		// 첫 실행시 현재 플레이어의 위치 초기화
		if (true == PrevPlayerPos_.IsZero2D())
		{
			PrevPlayerPos_ = TargetPlayer_->GetPosition();
		}

		// 플레이큐가 초기화 될때마다 다음 카메라 위치를 초기화
		NextPlayerPos_ = TargetPlayer_->GetPosition();
		// 카메라 키보드 조작용 변수 초기화
		PrevCameraPos_ = NextPlayerPos_;

		// 카메라 이동 후 Move페이즈로 
		LevelPhase_ = LevelFSM::SetDamagePlayer;

		break;
	case LevelFSM::Move:
	{
		std::list<Player*>& Teams = (*AllPlayerIter_);
		Player* CurrentPlayer = Teams.front();
		//CurrentPlayer->SetPlayerHp(50);
		CurrentPlayer->SetControlFlg(true);

		// 카메라 위치 이동
		// 무기를 발사하지 않았을경우 플레이어를 쫒아다님
		if (CurrentPlayer->GetPlayerState() != PlayerState::Action)
		{
			UpdateCamera(CurrentPlayer->GetPosition());
		}
		// 무기를 발사했을 경우 발사체를 쫒아다님
		else
		{
			// 무기 발사시 첫 프레임에 WeaponPosition이 0,0을 가르키는 문제가 있음.
			// 0,0을 가르킬경우 플레이어 포지션을 보도록
			if (CurrentPlayer->GetWeaponPos().CompareInt2D(float4::ZERO))
			{
				UpdateCamera(CurrentPlayer->GetPosition());
			}
			// 첫 프레임이 지나면 카메라가 무기를 보도록
			else
			{
				CurrentWeaponPos_ = CurrentPlayer->GetWeaponPos();
				UpdateCamera(CurrentWeaponPos_);
			}
		}

		// 움직임이 끝나면(true) 턴종료
		if (true == CurrentPlayer->ControllUpdate())
		{
			CurrentPlayer->SetTurnEndFlg(false);
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// 턴이 넘어갈때 Lerp처리 타이머를 초기화
				LerpTimer_ = 0.0f;

				// 카메라 이동 페이즈
				LevelPhase_ = LevelFSM::SetDamagePlayer;
			}
		}
		// TODO::턴바꿈용 임시코드
		// 턴종료
		//else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
		//{
		//	Teams.pop_front();

		//	if (Teams.size() != 0)
		//	{
		//		// 턴이 넘어갈때 Lerp처리 타이머를 초기화
		//		LerpTimer_ = 0.0f;

		//		// 카메라 이동 페이즈
		//		LevelPhase_ = LevelFSM::SetDamagePlayer;
		//	}
		//}
		else
		{
			// 턴 종료 조건을 만족하지 못하면 리턴
// PlayLevel->Update()에서 할 처리가 있다면 이 Return 위에서 작성할 것 ------------------------------------------------------------------------------------------------
			return;
		}

		// 다음 팀를 정해야 하는데.
		// 그 팀에 행동할 사람이 없다면
		if (Teams.size() == 0)
		{
			// 그 팀은 파괴하고
			AllPlayerIter_ = PlayQueue_.erase(AllPlayerIter_);

			// 만약에 팀조차도 하나도 없다면
			if (0 == PlayQueue_.size())
			{
				// 다시 팀을 정해주러 간다.
				LevelPhase_ = LevelFSM::Ready;
				return;
			}
		}
		else
		{
			// 그냥 다음팀으로 간다.
			++AllPlayerIter_;
		}

		if (AllPlayerIter_ == PlayQueue_.end())
		{
			AllPlayerIter_ = PlayQueue_.begin();
		}

		// 이전 플레이어의 위치 취득
		PrevPlayerPos_ = CurrentPlayer->GetPosition();
		// 다음 플레이어의 위치 취득
		NextPlayerPos_ = (*AllPlayerIter_).front()->GetPosition();
		//(*AllPlayerIter_).front()->SetControlFlg(true);

		LevelPhase_ = LevelFSM::SetDamagePlayer;

	}
	break;
	case LevelFSM::CameraMove:
	{
		LerpTimer_ += GameEngineTime::GetDeltaTime();

		if (CurrentWeaponPos_.IsZero2D() == false)
		{
			LerpStartCameraPos_ = CurrentWeaponPos_;
		}
		else
		{
			LerpStartCameraPos_ = PrevPlayerPos_;
		}
		
		float4 LerpCameraPos_ = float4::LerpLimit(LerpStartCameraPos_, NextPlayerPos_, LerpTimer_);

		// 카메라의 위치가 다음 플레이어의 위치와 같아지면 페이즈 종료
		if (LerpCameraPos_.CompareInt2D(NextPlayerPos_))
		{
			// Move턴으로 변경될때 바람세기 조정
			GameEngineRandom Ran;
			int WinInt = Ran.RandomInt(0, 1);

			SetWindUI(WinInt);
			CameraControledByWASDFlg_ = false;
			PrevCameraPos_ = LerpCameraPos_;
			//GameEngineSound::SoundPlayOneShot("HELLO.WAV");
			SoundPlayer_Hello_ = GameEngineSound::SoundPlayControl("HELLO.WAV");
			SoundPlayer_Hello_.Volume(0.1f);
			LevelPhase_ = LevelFSM::Move;
		}
		else
		{
			UpdateCamera(LerpCameraPos_);
		}

	}
	break;
	// 데미지 계산
	case LevelFSM::Damage:
	{
		// 데미지를 받은 캐릭터가 없으면 체력 계산 후 턴종료
		if (true == NextDamagedPlayerPos_.IsZero2D())
		{
			// 팀별 전체 체력 계산
			static bool IsTeamHpCalculated = false; // 계산 한번 하도록
			if (false == IsTeamHpCalculated)
			{
				std::vector<int> TeamsHp;
				for (std::list<Player*>& Team : AllPlayer_)
				{
					int TeamHp = 0;
					for (Player* Player : Team)
					{
						if (Player->GetIsDeath())
						{
							continue;
						}

						TeamHp += Player->GetPlayerHp();
					}
					TeamsHp.push_back(TeamHp);
				}

				// 체력바 줄어들기 & 체력 높은 순 정렬
				TeamHpBarListActor_->SetNewTeamsHp(TeamsHp);
				IsTeamHpCalculated = true;
			}

			IsTeamHpCalculated = false;
			LevelPhase_ = LevelFSM::CameraMove;

		}
		else
		{
			if (DamagedCharCameraDelayTimer_->GetAccTime() >= 1.5f)
			{
				// 플레이어 체력 감소

				// 카메라 이동
				LerpTimer_ += GameEngineTime::GetDeltaTime();

				LerpStartCameraPos_ = PrevPlayerPos_;

				float4 LerpCameraPos_ = float4::LerpLimit(LerpStartCameraPos_, NextDamagedPlayerPos_, LerpTimer_);

				// 카메라의 위치가 다음 플레이어의 위치와 같아지면 카메라 이동 종료
				if (LerpCameraPos_.CompareInt2D(NextDamagedPlayerPos_))
				{
					// 직전 플레이어의 위치를 저장(카메라 이동용)
					PrevPlayerPos_ = NextDamagedPlayerPos_;
					// 대기시간 타이머 초기화
					DamagedCharCameraDelayTimer_->ReSetAccTime();

					// 페이즈 이동
					LevelPhase_ = LevelFSM::SetDamagePlayer;
				}
			}
		}
	}
	break;
	case LevelFSM::SetDamagePlayer:
	{
		bool tmpFlg = false;
		NextDamagedPlayerPos_ = float4::ZERO;

		for (std::list<Player*>& Team : AllPlayer_)
		{
			for (Player* Player : Team)
			{
				if (Player->GetIsDeath())
				{
					continue;
				}
				if (Player->GetIsDamagedCam() == true)
				{
					Player->SetIsDamagedCam(false);
					NextDamagedPlayerPos_ = Player->GetPosition();
					tmpFlg = true;
					break;
				}
			}

			if (tmpFlg == true)
			{
				break;
			}
		}

		LerpTimer_ = 0.0f;
		LevelPhase_ = LevelFSM::Damage;
	}
	break;
	// 사망처리
	case LevelFSM::Death:
	{
		// TODO::PlayerHp가 없어서 테스트 불가능. 테스트 필요
		static bool DeathUpdateFlg = false;

		if (DeathList_.size() != 0)
		{
			for (std::list<Player*>& Team : AllPlayer_)
			{

				for (Player* Player : Team)
				{
					if (Player->GetIsDeath())
					{
						// IsDeath이면서 DeathUpdate가 끝나지 않은경우
						DeathUpdateFlg = true;

						// 죽음처리
					/*	if (true == Player->DeathUpdate())
						{
							DeathUpdateFlg = false;
							break;
						}*/
					}
				}

				// 반복중에 죽음처리를 하고 있는 플레이어가 있으면 멈추기
				if (true == DeathUpdateFlg)
				{
					// 반복문 탈출
					break;
				}
			}
		}
		else
		{
			// 사망처리를 할 플레이어가 없으면 카메라 이동 페이즈로
			LevelPhase_ = LevelFSM::CameraMove;
		}
	}
	break;

	default:
		break;
	}

	// 직전 페이즈의 정보를 저장
	PrevPhase_ = LevelPhase_;
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	static int teamColor = static_cast<int>(TeamColor::Red);
	PlayerColorTeamSetting_ = GameOptions::PlayingOptions.GetPlayerTeamSetting();

	// 팀 = 색깔 -> 색이 같으면 같은 팀
	// 각 팀 색깔의 배열에 랜덤으로 플레이어를 집어넣고 각 팀이 번갈아 가면서 턴을 가짐
	// ex) R1, R2, B1이 있으면 턴 순서는  R1->B1->R2->B1->R1 .... 
	// -> R1, R2중 누가 먼저 할 것인가는 랜덤
	// 플레이어가 색깔, 팀별로 생성되도록
	for (int TeamSetNum = 0; TeamSetNum < (int)TeamColor::Max; TeamSetNum++)
	{
		std::list<Player*> Playerlist;
		std::map<TeamColor, int>::iterator iTeamName
			= PlayerColorTeamSetting_.find((TeamColor)TeamSetNum);

		// 색이 없을 경우 다음 색으로
		if (iTeamName == PlayerColorTeamSetting_.end())
		{
			continue;
		}
		// 플레이어 생성
		for (int PlayerNum = 0; PlayerNum < iTeamName->second; PlayerNum++)
		{
			int tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER - 1);

			for (;;)
			{
				// 이미 사용된 포지션이라면
				if (true == GameMapInfo_->GetPosFlg(tmpRandom))
				{
					tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER - 1);

					continue;
				}

				// 사용된적이 없는 포지션이라면 탈출
				break;
			}


			GameMapInfo_->SetPosFlg(true, tmpRandom);
			Player_[TeamSetNum][PlayerNum] = CreateActor<Player>();
			//// TODO::로비레벨에서 넘어오도록 수정
			//// Player_->SetPlayerHp(GameOptions_->PlayingOptions.GetWormzHp());
			Player_[TeamSetNum][PlayerNum]->SetPlayerHp(100);
			Player_[TeamSetNum][PlayerNum]->SetMyTeamColor(static_cast<TeamColor>(TeamSetNum));
			Player_[TeamSetNum][PlayerNum]->SetPosition(GameMapInfo_->GetResponPosition(tmpRandom));

			//플레이어 색 지정
			Player_[TeamSetNum][PlayerNum]->CreateHpBar(100, { 0,0 }, (static_cast<FONT_COLOR>(TeamSetNum)));

			//화살표
			Player_[TeamSetNum][PlayerNum]->CreateControlArrow(static_cast<TeamColor>(TeamSetNum));
			// 팀에 플레이어를 추가
			Playerlist.push_back(Player_[TeamSetNum][PlayerNum]);


		}

		teamColor++;
		// 팀을 전체 플레이어 리스트에 추가
		AllPlayer_.push_back(Playerlist);

		// 팀 수, 팀원 수(UI) 설정
		TeamHpBarListActor_->AddTeamHpBar(TeamSetNum, static_cast<int>(Playerlist.size()));
	}

	TeamHpBarListActor_->InitTeamsHpBar((int)AllPlayer_.size());

	PlayShootingStar_->SetPosition({0,0});

	SoundPlayer_BGM_ = GameEngineSound::SoundPlayControl("ingame-11-rain&surf.wav", 100);
	SoundPlayer_BGM_.Volume(0.1f);
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	SoundPlayer_BGM_.Stop();

}

void PlayLevel::UpdateCamera(float4 _CameraPos)
{
	float CurrentLevelH = 0.0f;
	float CurrentLevelW = 0.0f;
	float4 CurMousePos = Mouse_->GetPosition();

	// MAPBOOKS 화면에서의 설정
	CurrentLevelH = static_cast<float>(SCALE_CAMERA_MAPMOOKS_Y);
	CurrentLevelW = static_cast<float>(SCALE_CAMERA_MAPMOOKS_X);

	// 카메라가 마우스에 의해 이동중이면 받아온 Position을 사용하지 않음.
	if (CameraControledByWASDFlg_ == true)
	{
		_CameraPos = PrevCameraPos_;
	}

	// 이전 위치의 마우스와 비교하여 이동했으면 카메라를 따라서 이동
	if (true == GameEngineInput::GetInst()->IsPress(KEY_CAMERAMOVE_LEFT))
	{
		_CameraPos.x -= 10.0f;
		CameraControledByWASDFlg_ = true;
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_CAMERAMOVE_RIGHT))
	{
		_CameraPos.x += 10.0f;
		CameraControledByWASDFlg_ = true;
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_CAMERAMOVE_UP))
	{
		_CameraPos.y -= 10.0f;
		CameraControledByWASDFlg_ = true;
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_CAMERAMOVE_DOWN))
	{
		_CameraPos.y += 10.0f;
		CameraControledByWASDFlg_ = true;
	}

	PrevCameraPos_ = _CameraPos;

	CameraPos_ = _CameraPos - GameEngineWindow::GetInst().GetScale().Half();

	// 카메라가 맵 범위를 벗어났을경우 재위치
	if (CameraPos_.x <= 0)
	{
		CameraPos_.x = 0;
	}
	if (CameraPos_.x >= CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix())
	{
		CameraPos_.x = CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix();
	}
	if (CameraPos_.y <= 0)
	{
		CameraPos_.y = 0;
	}
	if (CameraPos_.y >= CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy())
	{
		CameraPos_.y = CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy();
	}

	// 카메라 위치 갱신
	SetCameraPos(CameraPos_);
}

void PlayLevel::SetWindUI(int _WindDir)
{
	//바람 방향이 왼쪽이라면
	if (_WindDir == (int)WindType::Left)
	{
		GameEngineRandom Ran;

		PlayShootingStar_->SetLeftDir();

		//바람 세기를 랜덤하게 받는다
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		//바람게이지UI에 바람방향과 속도를 넘겨준다
		WindDir_ = float4::LEFT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Left, WindSpeed_);
		//구름Actor에도 넘겨준다

		GameMapInfo_->SetLargeCloudDir(_WindDir, WindSpeed_);
		GameMapInfo_->SetMiddleCloudDir(_WindDir, WindSpeed_);
		GameMapInfo_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
	else
	{
		GameEngineRandom Ran;

		PlayShootingStar_->SetRightDir();

		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		WindDir_ = float4::RIGHT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Right, WindSpeed_);
		GameMapInfo_->SetLargeCloudDir(_WindDir, WindSpeed_);
		GameMapInfo_->SetMiddleCloudDir(_WindDir, WindSpeed_);
		GameMapInfo_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
}

void PlayLevel::PlayerDamagedCheck4AirStrike()
{
	for (int i = 0; i < 5; i++)
	{
		AirBomb* tmpWeaponActor = dynamic_cast<AirBomb*>(WeaponMaster_->AirBombArr_[i]);
		float4 tmpWeaponActorPos = float4::ZERO;

		if (tmpWeaponActor != nullptr)
		{
			tmpWeaponActorPos = tmpWeaponActor->GetPosition();
		}

		if (tmpWeaponActor != nullptr && tmpWeaponActor->GetAirBombExplodEnd() == true)
		{
			for (std::list<Player*>& Team : AllPlayer_)
			{
				for (Player* Player : Team)
				{
					if (Player->GetIsDeath())
					{
						continue;
					}

					// 플레이어에게 데미지 판정
					Player->Damaged(tmpWeaponActorPos);
					

					// 끝난 폭탄에 대한 Death, nullptr
					if (WeaponMaster_->AirBombArr_[i] != nullptr)
					{
						WeaponMaster_->AirBombArr_[i]->Death();
						WeaponMaster_->AirBombArr_[i] = nullptr;
					}
				}
			}
		}

	}
}

void PlayLevel::PlayerDamagedCheck4NormalWeapon()
{
	float4 tmpWeaponActorPos = float4::ZERO;

	if (WeaponMaster_->ExplodeWeapon_ != nullptr)
	{
		tmpWeaponActorPos = WeaponMaster_->ExplodeWeapon_->GetPosition();
	}

	if (WeaponMaster_->ExplodeWeapon_ != nullptr 
		&& WeaponMaster_->GetExplodEndFlg() == false)
	{
		for (std::list<Player*>& Team : AllPlayer_)
		{
			for (Player* Player : Team)
			{
				if (Player->GetIsDeath())
				{
					continue;
				}

				// 플레이어에게 데미지 판정
				Player->Damaged(tmpWeaponActorPos);


			}
		}

		// 끝난 폭탄에 대한 Death, nullptr
		if (WeaponMaster_->ExplodeWeapon_ != nullptr)
		{
			WeaponMaster_->ExplodeWeapon_->Death();
			WeaponMaster_->ExplodeWeapon_ = nullptr;
		}
	}
}