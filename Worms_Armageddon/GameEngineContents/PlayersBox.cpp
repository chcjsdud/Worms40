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
	BoxRenderer_ = CreateRenderer("4459.bmp", static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetScale(float4{ 222, 258 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void PlayersBox::Update()
{
}


