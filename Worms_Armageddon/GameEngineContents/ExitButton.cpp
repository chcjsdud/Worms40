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
	Button::ButtonInit("Exit", float4{ 294, 46 }, true);
}

void ExitButton::Update()
{
	Button::ButtonUpdate();
}

void ExitButton::OnClickButton()
{
}

