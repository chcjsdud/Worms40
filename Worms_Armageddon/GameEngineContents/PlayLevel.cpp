#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "PlayLevelTestMouse.h"
#include "Player.h"
#include "Baz.h"
#include <GameEngineBase/GameEngineInput.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{

}

void PlayLevel::Loading()
{
	// 테스트용 코드
	PlayLevelTestMap_ = CreateActor<PlayLevelTestMap>();
	
	PlayLevelTestMouse_ = CreateActor<PlayLevelTestMouse>();

	BazTset_ = CreateActor<Baz>();
	// 테스트용 코드

	// TODO::수정
	//Player_ = CreateActor<Player>();

	if (false == GameEngineInput::GetInst()->IsKey("TestClick"))
	{
		GameEngineInput::GetInst()->CreateKey("TestClick", VK_LBUTTON);
	}

}

void PlayLevel::Update()
{

	if (GameEngineInput::GetInst()->IsDown("TestClick"))
	{
		int a = 0;
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{


}

void PlayLevel::CreateTestBullet()
{

}

