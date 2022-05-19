#include "ExitButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ExitButton::ExitButton() 
{
}

ExitButton::~ExitButton() 
{
}

void ExitButton::Start()
{
	BoxRenderer_ = CreateRenderer("Exit_Btn.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({ 294, 46});
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void ExitButton::Update()
{
}

