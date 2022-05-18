#include "PlayersBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

PlayersBox::PlayersBox() 
{
}

PlayersBox::~PlayersBox() 
{
}

void PlayersBox::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(RenderOrder::UI));
	Renderer_->SetImage("4459.bmp");
	Renderer_->SetPivot(float4{ 130, 140 });
}

void PlayersBox::Update()
{
}

