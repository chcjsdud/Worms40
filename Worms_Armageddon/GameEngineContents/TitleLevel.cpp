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

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}

	//if (true == GameEngineInput::GetInst()->IsPress("ChangeLobbyLevel"))
	//{
	//	GameEngine::GetInst().ChangeLevel("LobbyLevel");
	//}

}

