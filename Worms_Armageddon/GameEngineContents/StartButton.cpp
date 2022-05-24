#include "StartButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

StartButton::StartButton() 
{
}

StartButton::~StartButton() 
{
}

void StartButton::Start()
{
	ButtonInit("Start", float4{295, 68}, true);

	GameEngineRenderer* ButtonRenderer = Button::GetRenderer();
	ButtonRenderer->SetAlpha(100);

}

void StartButton::Update()
{
	Button::ButtonUpdate();
}

void StartButton::OnClickButton()
{
}

