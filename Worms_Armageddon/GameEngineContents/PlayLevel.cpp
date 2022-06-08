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
	// �׽�Ʈ�� �ڵ� ��

	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOUSE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_LEFT, VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_RIGHT, VK_RBUTTON);
	}

	WindSpeed_ = 45.0f;
}

void PlayLevel::Update()
{
	// ü�¹� ������

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

		// ù ����� ���� �÷��̾��� ��ġ �ʱ�ȭ
		if (true == PrevPlayerPos_.IsZero2D())
		{
			PrevPlayerPos_ = TargetPlayer_->GetPosition();
		}

		// �÷���ť�� �ʱ�ȭ �ɶ����� ���� ī�޶� ��ġ�� �ʱ�ȭ
		NextPlayerPos_ = TargetPlayer_->GetPosition();

		// ī�޶� �̵� �� Move������� 
		LevelPhase_ = LevelFSM::CameraMove;

		break;
	case LevelFSM::Move:
	{
		std::list<Player*>& Teams = (*AllPlayerIter_);
		Player* CurrentPlayer = Teams.front();

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
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// ���� �Ѿ�� Lerpó�� Ÿ�̸Ӹ� �ʱ�ȭ
				LerpTimer_ = 0.0f;

				// ī�޶� �̵� ������
				LevelPhase_ = LevelFSM::CameraMove;
			}
		}
		// TODO::�Ϲٲ޿� �ӽ��ڵ�
		// ������
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
		{
			Teams.pop_front();

			if (Teams.size() != 0)
			{
				// ���� �Ѿ�� Lerpó�� Ÿ�̸Ӹ� �ʱ�ȭ
				LerpTimer_ = 0.0f;

				// ī�޶� �̵� ������
				LevelPhase_ = LevelFSM::CameraMove;
			}
		}
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
		// �÷��̾� ü�� ���


		// �� ü�� ���
		UpdateTeamHpBarUI();
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
						if (true == Player->DeathUpdate())
						{
							DeathUpdateFlg = false;
							break;
						}
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
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
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
			int tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER);

			for (;;)
			{
				// �̹� ���� �������̶��
				if (true == GameMapInfo_->GetPosFlg(tmpRandom))
				{
					tmpRandom = GameEngineRandom::MainRandom.RandomInt(0, PLAYER_MAX_NUMBER);

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
			Player_[TeamSetNum][PlayerNum]->SetPosition(GameMapInfo_->GetResponPosition(tmpRandom));

			// ���� �÷��̾ �߰�
			Playerlist.push_back(Player_[TeamSetNum][PlayerNum]);

		}

		// ���� ��ü �÷��̾� ����Ʈ�� �߰�
		AllPlayer_.push_back(Playerlist);

		// �� ü�¹� ���� ����
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

	// �׽�Ʈ�� �ڵ�
	CurrentLevelH = SCALE_CAMERA_MAPMOOKS_Y;
	CurrentLevelW = SCALE_CAMERA_MAPMOOKS_X;
	// �׽�Ʈ�� �ڵ�

	// TODO::��ź�� ���� ī�޶� ��ġ�� �����ϰų�
	// TODO::�÷��̾��� ��ġ�� ���缭 ī�޶� ����ٴϰų��� 2���� ���
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

		//�ٶ� ���⸦ �����ϰ� �޴´�
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		//�ٶ�������UI�� �ٶ������ �ӵ��� �Ѱ��ش�
		WindDir_ = float4::LEFT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Left,WindSpeed_);
		//����Actor���� �Ѱ��ش�

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

// �� ü���� TeamHpBar�� ����
bool PlayLevel::UpdateTeamHpBarUI()
{
	// ���� ��ü ü�� ���
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

