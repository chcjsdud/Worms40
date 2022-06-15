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
	// �÷��̾� �迭 �ʱ�ȭ
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
	// �׽�Ʈ�� �ڵ�, �� ���ÿ� ���� �ٸ� ���� ����
	//���ȭ�� ����
	GameMapInfo_ = CreateActor<MapBooks>();
	// ī�޶� �����̿� Ÿ�̸� ����
	DamagedCharCameraDelayTimer_ = CreateActor<TimerActor>();

	// ���콺
	Mouse_ = CreateActor<Cursor>((int)ActorGroup::UI);
	// �ٶ� ������
	WindGaugeActor_ = CreateActor<WindGauge>((int)RenderOrder::UI);
	WindGaugeActor_->SetPosition({ 1180.0f, 940.0f });
	// �κ��丮
	InventoryActor_ = CreateActor<Inventory>((int)ActorGroup::UI);
	// �� HP��
	TeamHpBarListActor_ = CreateActor<TeamHpBarList>((int)ActorGroup::UI);

	// ���� ����
	WeaponMaster_ = CreateActor<WeaponMaster>();
	WeaponMaster_->SetGameMap(GameMapInfo_);

	//����������
	PlayShootingStar_ = CreateActor<PlayShootingStar>(static_cast<int>(ActorGroup::UI));

	// �׽�Ʈ�� �ڵ� ��
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

	// ���Ʈ��ũ
	PlayerDamagedCheck4AirStrike();
	// �Ϲݹ��⿡ ����
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

		// ���� ������ �÷��̾ ��� �������� ��� ũ���� ������
		if (AllPlayerIter_->size() == 0)
		{
			// 2�� ���
			Sleep(2000);

			GameEngine::GetInst().ChangeLevel(LEVEL_CREDIT_LEVEL);

			return;
		}

		TargetPlayer_ = *AllPlayerIter_->begin();

		// ù ����� ���� �÷��̾��� ��ġ �ʱ�ȭ
		if (true == PrevPlayerPos_.IsZero2D())
		{
			PrevPlayerPos_ = TargetPlayer_->GetPosition();
		}

		// �÷���ť�� �ʱ�ȭ �ɶ����� ���� ī�޶� ��ġ�� �ʱ�ȭ
		NextPlayerPos_ = TargetPlayer_->GetPosition();
		// ī�޶� Ű���� ���ۿ� ���� �ʱ�ȭ
		PrevCameraPos_ = NextPlayerPos_;

		// ī�޶� �̵� �� Move������� 
		LevelPhase_ = LevelFSM::SetDamagePlayer;

		break;
	case LevelFSM::Move:
	{
		std::list<Player*>& Teams = (*AllPlayerIter_);
		Player* CurrentPlayer = Teams.front();
		//CurrentPlayer->SetPlayerHp(50);
		CurrentPlayer->SetControlFlg(true);

		// ī�޶� ��ġ �̵�
		// ���⸦ �߻����� �ʾ������ �÷��̾ �i�ƴٴ�
		if (CurrentPlayer->GetPlayerState() != PlayerState::Action)
		{
			UpdateCamera(CurrentPlayer->GetPosition());
		}
		// ���⸦ �߻����� ��� �߻�ü�� �i�ƴٴ�
		else
		{
			// ���� �߻�� ù �����ӿ� WeaponPosition�� 0,0�� ����Ű�� ������ ����.
			// 0,0�� ����ų��� �÷��̾� �������� ������
			if (CurrentPlayer->GetWeaponPos().CompareInt2D(float4::ZERO))
			{
				UpdateCamera(CurrentPlayer->GetPosition());
			}
			// ù �������� ������ ī�޶� ���⸦ ������
			else
			{
				CurrentWeaponPos_ = CurrentPlayer->GetWeaponPos();
				UpdateCamera(CurrentWeaponPos_);
			}
		}

		// �������� ������(true) ������
		if (true == CurrentPlayer->ControllUpdate())
		{
			CurrentPlayer->SetTurnEndFlg(false);
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// ���� �Ѿ�� Lerpó�� Ÿ�̸Ӹ� �ʱ�ȭ
				LerpTimer_ = 0.0f;

				// ī�޶� �̵� ������
				LevelPhase_ = LevelFSM::SetDamagePlayer;
			}
		}
		// TODO::�Ϲٲ޿� �ӽ��ڵ�
		// ������
		//else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
		//{
		//	Teams.pop_front();

		//	if (Teams.size() != 0)
		//	{
		//		// ���� �Ѿ�� Lerpó�� Ÿ�̸Ӹ� �ʱ�ȭ
		//		LerpTimer_ = 0.0f;

		//		// ī�޶� �̵� ������
		//		LevelPhase_ = LevelFSM::SetDamagePlayer;
		//	}
		//}
		else
		{
			// �� ���� ������ �������� ���ϸ� ����
// PlayLevel->Update()���� �� ó���� �ִٸ� �� Return ������ �ۼ��� �� ------------------------------------------------------------------------------------------------
			return;
		}

		// ���� ���� ���ؾ� �ϴµ�.
		// �� ���� �ൿ�� ����� ���ٸ�
		if (Teams.size() == 0)
		{
			// �� ���� �ı��ϰ�
			AllPlayerIter_ = PlayQueue_.erase(AllPlayerIter_);

			// ���࿡ �������� �ϳ��� ���ٸ�
			if (0 == PlayQueue_.size())
			{
				// �ٽ� ���� �����ַ� ����.
				LevelPhase_ = LevelFSM::Ready;
				return;
			}
		}
		else
		{
			// �׳� ���������� ����.
			++AllPlayerIter_;
		}

		if (AllPlayerIter_ == PlayQueue_.end())
		{
			AllPlayerIter_ = PlayQueue_.begin();
		}

		// ���� �÷��̾��� ��ġ ���
		PrevPlayerPos_ = CurrentPlayer->GetPosition();
		// ���� �÷��̾��� ��ġ ���
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

		// ī�޶��� ��ġ�� ���� �÷��̾��� ��ġ�� �������� ������ ����
		if (LerpCameraPos_.CompareInt2D(NextPlayerPos_))
		{
			// Move������ ����ɶ� �ٶ����� ����
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
	// ������ ���
	case LevelFSM::Damage:
	{
		// �������� ���� ĳ���Ͱ� ������ ü�� ��� �� ������
		if (true == NextDamagedPlayerPos_.IsZero2D())
		{
			// ���� ��ü ü�� ���
			static bool IsTeamHpCalculated = false; // ��� �ѹ� �ϵ���
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

				// ü�¹� �پ��� & ü�� ���� �� ����
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
				// �÷��̾� ü�� ����

				// ī�޶� �̵�
				LerpTimer_ += GameEngineTime::GetDeltaTime();

				LerpStartCameraPos_ = PrevPlayerPos_;

				float4 LerpCameraPos_ = float4::LerpLimit(LerpStartCameraPos_, NextDamagedPlayerPos_, LerpTimer_);

				// ī�޶��� ��ġ�� ���� �÷��̾��� ��ġ�� �������� ī�޶� �̵� ����
				if (LerpCameraPos_.CompareInt2D(NextDamagedPlayerPos_))
				{
					// ���� �÷��̾��� ��ġ�� ����(ī�޶� �̵���)
					PrevPlayerPos_ = NextDamagedPlayerPos_;
					// ���ð� Ÿ�̸� �ʱ�ȭ
					DamagedCharCameraDelayTimer_->ReSetAccTime();

					// ������ �̵�
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
	// ���ó��
	case LevelFSM::Death:
	{
		// TODO::PlayerHp�� ��� �׽�Ʈ �Ұ���. �׽�Ʈ �ʿ�
		static bool DeathUpdateFlg = false;

		if (DeathList_.size() != 0)
		{
			for (std::list<Player*>& Team : AllPlayer_)
			{

				for (Player* Player : Team)
				{
					if (Player->GetIsDeath())
					{
						// IsDeath�̸鼭 DeathUpdate�� ������ �������
						DeathUpdateFlg = true;

						// ����ó��
					/*	if (true == Player->DeathUpdate())
						{
							DeathUpdateFlg = false;
							break;
						}*/
					}
				}

				// �ݺ��߿� ����ó���� �ϰ� �ִ� �÷��̾ ������ ���߱�
				if (true == DeathUpdateFlg)
				{
					// �ݺ��� Ż��
					break;
				}
			}
		}
		else
		{
			// ���ó���� �� �÷��̾ ������ ī�޶� �̵� �������
			LevelPhase_ = LevelFSM::CameraMove;
		}
	}
	break;

	default:
		break;
	}

	// ���� �������� ������ ����
	PrevPhase_ = LevelPhase_;
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	static int teamColor = static_cast<int>(TeamColor::Red);
	PlayerColorTeamSetting_ = GameOptions::PlayingOptions.GetPlayerTeamSetting();

	// �� = ���� -> ���� ������ ���� ��
	// �� �� ������ �迭�� �������� �÷��̾ ����ְ� �� ���� ������ ���鼭 ���� ����
	// ex) R1, R2, B1�� ������ �� ������  R1->B1->R2->B1->R1 .... 
	// -> R1, R2�� ���� ���� �� ���ΰ��� ����
	// �÷��̾ ����, ������ �����ǵ���
	for (int TeamSetNum = 0; TeamSetNum < (int)TeamColor::Max; TeamSetNum++)
	{
		std::list<Player*> Playerlist;
		std::map<TeamColor, int>::iterator iTeamName
			= PlayerColorTeamSetting_.find((TeamColor)TeamSetNum);

		// ���� ���� ��� ���� ������
		if (iTeamName == PlayerColorTeamSetting_.end())
		{
			continue;
		}
		// �÷��̾� ����
		for (int PlayerNum = 0; PlayerNum < iTeamName->second; PlayerNum++)
		{
			int tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER - 1);

			for (;;)
			{
				// �̹� ���� �������̶��
				if (true == GameMapInfo_->GetPosFlg(tmpRandom))
				{
					tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER - 1);

					continue;
				}

				// �������� ���� �������̶�� Ż��
				break;
			}


			GameMapInfo_->SetPosFlg(true, tmpRandom);
			Player_[TeamSetNum][PlayerNum] = CreateActor<Player>();
			//// TODO::�κ񷹺����� �Ѿ������ ����
			//// Player_->SetPlayerHp(GameOptions_->PlayingOptions.GetWormzHp());
			Player_[TeamSetNum][PlayerNum]->SetPlayerHp(100);
			Player_[TeamSetNum][PlayerNum]->SetMyTeamColor(static_cast<TeamColor>(TeamSetNum));
			Player_[TeamSetNum][PlayerNum]->SetPosition(GameMapInfo_->GetResponPosition(tmpRandom));

			//�÷��̾� �� ����
			Player_[TeamSetNum][PlayerNum]->CreateHpBar(100, { 0,0 }, (static_cast<FONT_COLOR>(TeamSetNum)));

			//ȭ��ǥ
			Player_[TeamSetNum][PlayerNum]->CreateControlArrow(static_cast<TeamColor>(TeamSetNum));
			// ���� �÷��̾ �߰�
			Playerlist.push_back(Player_[TeamSetNum][PlayerNum]);


		}

		teamColor++;
		// ���� ��ü �÷��̾� ����Ʈ�� �߰�
		AllPlayer_.push_back(Playerlist);

		// �� ��, ���� ��(UI) ����
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

	// MAPBOOKS ȭ�鿡���� ����
	CurrentLevelH = static_cast<float>(SCALE_CAMERA_MAPMOOKS_Y);
	CurrentLevelW = static_cast<float>(SCALE_CAMERA_MAPMOOKS_X);

	// ī�޶� ���콺�� ���� �̵����̸� �޾ƿ� Position�� ������� ����.
	if (CameraControledByWASDFlg_ == true)
	{
		_CameraPos = PrevCameraPos_;
	}

	// ���� ��ġ�� ���콺�� ���Ͽ� �̵������� ī�޶� ���� �̵�
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

	// ī�޶� �� ������ �������� ����ġ
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

	// ī�޶� ��ġ ����
	SetCameraPos(CameraPos_);
}

void PlayLevel::SetWindUI(int _WindDir)
{
	//�ٶ� ������ �����̶��
	if (_WindDir == (int)WindType::Left)
	{
		GameEngineRandom Ran;

		PlayShootingStar_->SetLeftDir();

		//�ٶ� ���⸦ �����ϰ� �޴´�
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		//�ٶ�������UI�� �ٶ������ �ӵ��� �Ѱ��ش�
		WindDir_ = float4::LEFT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Left, WindSpeed_);
		//����Actor���� �Ѱ��ش�

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

					// �÷��̾�� ������ ����
					Player->Damaged(tmpWeaponActorPos);
					

					// ���� ��ź�� ���� Death, nullptr
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

				// �÷��̾�� ������ ����
				Player->Damaged(tmpWeaponActorPos);


			}
		}

		// ���� ��ź�� ���� Death, nullptr
		if (WeaponMaster_->ExplodeWeapon_ != nullptr)
		{
			WeaponMaster_->ExplodeWeapon_->Death();
			WeaponMaster_->ExplodeWeapon_ = nullptr;
		}
	}
}