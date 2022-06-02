#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "Player.h"
#include "WeaponMaster.h"
#include "Inventory.h"
#include "Cursor.h"
#include "MapBooks.h"
#include "GameOptions.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel::PlayLevel()
	: LevelPhase_(LevelFSM::Ready)
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

	//���콺
	Mouse_ = CreateActor<Cursor>((int)ActorGroup::UI);
	//�ٶ� ������
	WindGaugeActor_ = CreateActor<WindGauge>((int)RenderOrder::UI);
	WindGaugeActor_->SetPosition({ 1150.0f,20.0f });
	//�κ��丮
	Inventory_ = CreateActor<Inventory>((int)RenderOrder::UI);

	// ��� �̹���
	LargeCloudActor_ = CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200.0f,200.0f});
	SmallCloudActor_ = CreateActor<SmallCloud>();
	SmallCloudActor_->SetPosition({ 250.0f,200.0f });

	// TODO::�ʿ� ���� X������ ���� �ʿ�
	WaterActor_ = CreateActor<Water>();
	WaterActor_->SetPosition({ SCALE_MAPBOOKS_X / 2, 610.0f });

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
	if (DeathList_.size() != 0)
	{
		// ����ó��

		LevelPhase_ = LevelFSM::Death;
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

		TargetPlayer_ = *AllPlayerIter_->begin();

		// TODO::ī�޶��̵� �ۼ� �� �߰�
		// LevelPhase_ = LevelFSM::CameraMove;
		LevelPhase_ = LevelFSM::Move;

		break;
	case LevelFSM::Move:
		{
			std::list<Player*>& Teams = (*AllPlayerIter_);
			Player* CurrentPlayer = Teams.front();

			// ī�޶� ��ġ �̵�
			if (CurrentPlayer->GetPlayerState() != PlayerState::Action)
			{
				UpdateCamera(CurrentPlayer->GetPosition());
			}
			else
			{
				// ���� �߻�� ù �����ӿ� WeaponPosition�� 0,0�� ����Ű�� ������ ����.
				if (CurrentPlayer->GetWeaponPos().CompareInt2D(float4::ZERO))
				{
					UpdateCamera(CurrentPlayer->GetPosition());
				}
				// ù �������� ������ ī�޶� ���⸦ ������
				else
				{
					UpdateCamera(CurrentPlayer->GetWeaponPos());
				}
			}

			// ������
			if (true == CurrentPlayer->ControllUpdate())
			{
				Teams.pop_front();
			}
			// TODO::�Ϲٲ޿� �ӽ��ڵ�
			// ������
			else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
			{
				Teams.pop_front();
			}
			else
			{
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

		}
		break;
	case LevelFSM::CameraMove:

		if (nullptr == TargetPlayer_)
		{
			LevelPhase_ = LevelFSM::Move;
		}

		// ī�޶� ������ �����ϸ�ȴ�.

		break;
	default:
		break;
	}

	//�ӽù���
	//���콺 Ŭ���Ҷ����� �ٶ����� ����
	//if (GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
	//{
	//	GameEngineRandom Ran;
	//	int WinInt = Ran.RandomInt(0, 1);

	//	SetWindUI(WinInt);
	//}

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
	CurrentLevelH = LEN_MAPBOOKS_Y;
	CurrentLevelW = LEN_MAPBOOKS_X;
	// �׽�Ʈ�� �ڵ�

	// TODO::��ź�� ���� ī�޶� ��ġ�� �����ϰų�
	// TODO::�÷��̾��� ��ġ�� ���缭 ī�޶� ����ٴϰų��� 2���� ���
	CameraPos_ = _CameraPos - GameEngineWindow::GetInst().GetScale().Half();

	// ī�޶� �� ������ �������� ����ġ
	if (CameraPos_.x <= -CurrentLevelW / 2)
	{
		CameraPos_.x = -CurrentLevelW / 2;
	}
	if (CameraPos_.x >= CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix())
	{
		CameraPos_.x = CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix();
	}
	if (CameraPos_.y <= -CurrentLevelH / 2)
	{
		CameraPos_.y = 0;
	}
	if (CameraPos_.y >= CurrentLevelH / 2 - GameEngineWindow::GetInst().GetScale().iy())
	{
		CameraPos_.y = CurrentLevelH / 2 - GameEngineWindow::GetInst().GetScale().iy();
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

		LargeCloudActor_->SetLargeCloudDir(_WindDir, WindSpeed_);
		SmallCloudActor_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
	else
	{
		GameEngineRandom Ran;
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		WindDir_ = float4::RIGHT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Right, WindSpeed_);
		LargeCloudActor_->SetLargeCloudDir(_WindDir,WindSpeed_);
		SmallCloudActor_->SetSmallCloudDir(_WindDir, WindSpeed_);
	}
}

