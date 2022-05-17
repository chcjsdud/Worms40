#include "LobbyBackGround.h"
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
}

void LobbyBackGround::Update()
{

}

