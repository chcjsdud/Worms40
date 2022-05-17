#include "TitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineWindow.h"

TitleLevel::TitleLevel()
	:
	StartLogo_(nullptr)
{
}

TitleLevel::~TitleLevel() 
{

}

void TitleLevel::Loading()
{
	StartLogo_ = CreateActor<StartLogo>();
	StartLogo_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x, GameEngineWindow::GetInst().GetScale().Half().y });
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

