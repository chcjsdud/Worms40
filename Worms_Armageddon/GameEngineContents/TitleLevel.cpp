#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{

}

void TitleLevel::Loading()
{
}

void TitleLevel::Update()
{

	if (true == GameEngineInput::GetInst()->IsPress(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	//if (true == GameEngineInput::GetInst()->IsPress("ChangeLobbyLevel"))
	//{
	//	GameEngine::GetInst().ChangeLevel("LobbyLevel");
	//}

}

