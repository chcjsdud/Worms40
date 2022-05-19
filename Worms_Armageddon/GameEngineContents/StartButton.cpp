#include "StartButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

StartButton::StartButton() 
	: ButtonRenderer_(nullptr)
{
}

StartButton::~StartButton() 
{
}

void StartButton::Start()
{
	ButtonRenderer_ = CreateRenderer("Btn_Start_Idle.bmp", (int)RenderOrder::UI);
	ButtonRenderer_->SetScale({ 295, 68 });
	ButtonRenderer_->SetAlpha(100);
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());
}

void StartButton::Update()
{
}

