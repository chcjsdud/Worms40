#include "ReadyButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ReadyButton::ReadyButton() 
{
}

ReadyButton::~ReadyButton() 
{
}

void ReadyButton::Start()
{
	BoxRenderer_ = CreateRenderer("OFF_btn.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({ 217, 154 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

}

void ReadyButton::Update()
{
}

