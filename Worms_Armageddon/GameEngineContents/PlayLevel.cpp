#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "Player.h"
#include "WeaponMaster.h"
#include "Cursor.h"
#include "MapBooks.h"
#include "GameOptions.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <GameEngineBase/GameEngineInput.h>

PlayLevel::PlayLevel()
	: LevelPhase_(LevelFSM::Ready)
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

	//마우스
	Mouse_ = CreateActor<Cursor>((int)ActorGroup::UI);
	//바람 게이지
	WindGaugeActor_ = CreateActor<WindGauge>((int)RenderOrder::UI);
	WindGaugeActor_->SetPosition({ 1150.0f,20.0f });

	// 배경 이미지
	LargeCloudActor_ = CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200.0f,200.0f});
	SmallCloudActor_ = CreateActor<SmallCloud>();
	SmallCloudActor_->SetPosition({ 250.0f,200.0f });
	WaterActor_ = CreateActor<Water>();
	WaterActor_->SetPosition({ 300.0f,300.0f });

	// 무기 설정
	WeaponMaster_ = CreateActor<WeaponMaster>();
	WeaponMaster_->SetGameMap(GameMapInfo_);
	// 테스트용 코드 끝

	if (false == GameEngineInput::GetInst()->IsKey("TestClick"))
	{
		GameEngineInput::GetInst()->CreateKey("TestClick", VK_LBUTTON);
	}

	WindSpeed_ = 45.0f;
}

void PlayLevel::Update()
{
	if (DeathList_.size() != 0)
	{
		// 죽음처리

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

		// TODO::카메라이동 작성 후 추가
		// LevelPhase_ = LevelFSM::CameraMove;
		LevelPhase_ = LevelFSM::Move;

		break;
	case LevelFSM::Move:
		{
			std::list<Player*>& Teams = (*AllPlayerIter_);
			Player* CurrentPlayer = Teams.front();

			// 움직여


			// 턴종료
			if (true == CurrentPlayer->ControllUpdate())
			{
				Teams.pop_front();
			}
			// TODO::턴바꿈용 임시코드
			else if (true == GameEngineInput::GetInst()->IsUp("TestClick"))
			{
				Teams.pop_front();
			}
			else
			{
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

		}
		break;
	case LevelFSM::CameraMove:

		if (nullptr == TargetPlayer_)
		{
			LevelPhase_ = LevelFSM::Move;
		}

		// 카메라 로직을 실행하면된다.

		break;
	default:
		break;
	}

	//임시방편
	//마우스 클릭할때마다 바람세기 변경
	if (GameEngineInput::GetInst()->IsDown("TestClick"))
	{
		GameEngineRandom Ran;
		int WinInt = Ran.RandomInt(0, 1);

		SetWindUI(WinInt);
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
	}
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{


}

void PlayLevel::CreateTestBullet()
{

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

