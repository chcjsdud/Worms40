#include "StartButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

StartButton::StartButton() 
{
}

StartButton::~StartButton() 
{
}

void StartButton::Start()
{
	BoxRenderer_ = CreateRenderer("Start_Btn.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({ 295, 68 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void StartButton::Update()
{
}

