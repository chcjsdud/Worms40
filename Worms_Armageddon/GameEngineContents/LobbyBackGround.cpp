#include "LobbyBackGround.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

LobbyBackGround::LobbyBackGround()
	: BackGround_(nullptr)
{
}

LobbyBackGround::~LobbyBackGround()
{
}

void LobbyBackGround::Start()
{
	BackGround_ = CreateRenderer(static_cast<int>(RenderOrder::BackGround_0));
	//BackGround_->SetImage("LobbyBackground.bmp");
	BackGround_->SetImage("BlueGrad.bmp");
	BackGround_->SetPivot(GameEngineWindow::GetScale().Half());
	BackGround_->SetScale(GameEngineWindow::GetScale());
}

void LobbyBackGround::Update()
{

}

