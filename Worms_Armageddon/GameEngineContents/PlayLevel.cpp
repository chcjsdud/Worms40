#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "PlayLevelTestMouse.h"
#include <GameEngineBase/GameEngineInput.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	PlayLevelTestMap_ = CreateActor<PlayLevelTestMap>();
	
	PlayLevelTestMouse_ = CreateActor<PlayLevelTestMouse>();

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

