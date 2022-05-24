#include "ExitButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ExitButton::ExitButton() 
	: ButtonRenderer_(nullptr)
{
}

ExitButton::~ExitButton() 
{
}

void ExitButton::Start()
{
	ButtonRenderer_ = CreateRenderer("Btn_Exit_Idle.bmp", (int)RenderOrder::UI);
	ButtonRenderer_->SetScale({ 294, 46});
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());
}

void ExitButton::Update()
{
}

