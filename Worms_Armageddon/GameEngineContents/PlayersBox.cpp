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
	Renderer_->SetScale(float4{ 222, 257 });
	Renderer_->SetPivot(Renderer_->GetScale().Half());
}

void PlayersBox::Update()
{
}


