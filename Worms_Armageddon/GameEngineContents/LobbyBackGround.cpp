#include "LobbyBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

LobbyBackGround::LobbyBackGround()
{
}

LobbyBackGround::~LobbyBackGround()
{
}

void LobbyBackGround::Start()
{
	BackGround_ = CreateRenderer(0);
	BackGround_->SetImage("LobbyImage.bmp");
	BackGround_->SetPivot(GameEngineWindow::GetScale().Half());
	BackGround_->SetScale(GameEngineWindow::GetScale());
}

void LobbyBackGround::Update()
{

}

