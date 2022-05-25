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
{
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
	// 플레이어가 여럿이 나오도록 수정
	for (int i = 0; i < GameOptions::PlayingOptions.GetPlayerNum(); i++)
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

		Player_[i] = CreateActor<Player>();

		// TODO::로비레벨에서 넘어오도록 수정
		// Player_->SetPlayerHp(GameOptions_->PlayingOptions.GetWormzHp());
		Player_[i]->SetPlayerHp(100);
		Player_[i]->SetPosition(GameMapInfo_->GetResponPosition(tmpRandom));
		GameMapInfo_->SetPosFlg(true, tmpRandom);


		// 팀 = 색깔 -> 색이 같으면 같은 팀
		// 각 팀 색깔의 배열에 랜덤으로 플레이어를 집어넣고 각 팀이 번갈아 가면서 턴을 가짐
		// ex) R1, R2, B1이 있으면 턴 순서는  R1->B1->R2->B1->R1 .... 
		// -> R1, R2중 누가 먼저 할 것인가는 랜덤
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

