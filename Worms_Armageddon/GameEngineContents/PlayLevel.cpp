#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "Player.h"
#include "WeaponMaster.h"
#include "Inventory.h"
#include "Cursor.h"
#include "MapBooks.h"
#include "TeamHpBarList.h"
#include "GameOptions.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel::PlayLevel()
	: LevelPhase_(LevelFSM::Ready)
	, LerpTimer_(0.0f)
	, PrevPlayerPos_(float4::ZERO)
	, NextPlayerPos_(float4::ZERO)
	, LerpStartCameraPos_(float4::ZERO)
	, CurrentWeaponPos_(float4::ZERO)
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
	// 테스트용 코드 끝

	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOUSE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_LEFT, VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_RIGHT, VK_RBUTTON);
	}

	WindSpeed_ = 45.0f;
}

void PlayLevel::Update()
{
	// 체력바 디버깅용

	//{
	//	LevelPhase_ = LevelFSM::Damage;
	//}

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
		TargetPlayer_ = *AllPlayerIter_->begin();

		// 첫 실행시 현재 플레이어의 위치 초기화
		if (true == PrevPlayerPos_.IsZero2D())
		{
			PrevPlayerPos_ = TargetPlayer_->GetPosition();
		}

		// 플레이큐가 초기화 될때마다 다음 카메라 위치를 초기화
		NextPlayerPos_ = TargetPlayer_->GetPosition();

		// 카메라 이동 후 Move페이즈로 
		LevelPhase_ = LevelFSM::CameraMove;

		break;
	case LevelFSM::Move:
	{
		std::list<Player*>& Teams = (*AllPlayerIter_);
		Player* CurrentPlayer = Teams.front();

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
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// 턴이 넘어갈때 Lerp처리 타이머를 초기화
				LerpTimer_ = 0.0f;

				// 카메라 이동 페이즈
				LevelPhase_ = LevelFSM::CameraMove;
			}
		}
		// TODO::턴바꿈용 임시코드
		// 턴종료
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
		{
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// 턴이 넘어갈때 Lerp처리 타이머를 초기화
				LerpTimer_ = 0.0f;

				// 카메라 이동 페이즈
				LevelPhase_ = LevelFSM::CameraMove;
			}
		}
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
		// 플레이어 체력 계산


		// 팀 체력 계산
		UpdateTeamHpBarUI();
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
						if (true == Player->DeathUpdate())
						{
							DeathUpdateFlg = false;
							break;
						}
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
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
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
			int tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER);

			for (;;)
			{
				// 이미 사용된 포지션이라면
				if (true == GameMapInfo_->GetPosFlg(tmpRandom))
				{
					tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER);

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
			Player_[TeamSetNum][PlayerNum]->SetPosition(GameMapInfo_->GetResponPosition(tmpRandom));

			// 팀에 플레이어를 추가
			Playerlist.push_back(Player_[TeamSetNum][PlayerNum]);

		}

		// 팀을 전체 플레이어 리스트에 추가
		AllPlayer_.push_back(Playerlist);

		// 팀 체력바 개수 설정
		TeamHpBarListActor_->InitTeamSize(Playerlist.size());
	}
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{


}

void PlayLevel::CreateTestBullet()
{

}

void PlayLevel::UpdateCamera(float4 _CameraPos)
{
	float CurrentLevelH = 0.0f;
	float CurrentLevelW = 0.0f;

	// 테스트용 코드
	CurrentLevelH = SCALE_CAMERA_MAPMOOKS_Y;
	CurrentLevelW = SCALE_CAMERA_MAPMOOKS_X;
	// 테스트용 코드

	// TODO::포탄에 따라서 카메라 위치를 변경하거나
	// TODO::플레이어의 위치에 맞춰서 카메라가 따라다니거나의 2가지 모드
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

		//바람 세기를 랜덤하게 받는다
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		//바람게이지UI에 바람방향과 속도를 넘겨준다
		WindDir_ = float4::LEFT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Left,WindSpeed_);
		//구름Actor에도 넘겨준다

		GameMapInfo_->SetLargeCloudDir(_WindDir, WindSpeed_);
		GameMapInfo_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
	else
	{
		GameEngineRandom Ran;
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		WindDir_ = float4::RIGHT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Right, WindSpeed_);
		GameMapInfo_->SetLargeCloudDir(_WindDir,WindSpeed_);
		GameMapInfo_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
}

// 팀 체력을 TeamHpBar에 전달
bool PlayLevel::UpdateTeamHpBarUI()
{
	// 팀별 전체 체력 계산
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
	
	TeamHpBarListActor_->SetTeamsHpInfo(&TeamsHp);

	return false;
}

