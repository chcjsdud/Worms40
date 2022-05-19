#include "ReadyButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

const float ButtonSizeX = 217.0f;
const float ButtonSizeY = 154.0f;

ReadyButton::ReadyButton() 
{
}

ReadyButton::~ReadyButton() 
{
}

void ReadyButton::Start()
{
	BoxRenderer_ = CreateRenderer("OFF_btn.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({ ButtonSizeX, ButtonSizeY });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

}

void ReadyButton::Update()
{
}

