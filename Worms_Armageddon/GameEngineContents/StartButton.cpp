#include "StartButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

StartButton::StartButton()
	: IsGameStart_(false)
	, ButtonRenderer_(nullptr)
{
}

StartButton::~StartButton() 
{
}

void StartButton::Start()
{
	IsGameStart_ = false;

	ButtonInit("Start", float4{295, 68}, true);

	ButtonRenderer_ = Button::GetRenderer();

	SetActivate(false);
}

void StartButton::Update()
{
	ActivateCheck();
	Button::ButtonUpdate();
	OnClickButton();
}

void StartButton::OnClickButton()
{
	if (MOUSE_STATE::MOUSE_CLICK_LEFT == GetMouseState())
	{
		IsGameStart_ = true;
	}
}

void StartButton::ActivateCheck()
{
	bool Value = Button::GetActivate();
	if (true == Value)
	{
		ButtonRenderer_->SetAlpha(255);
	}
	else
	{
		ButtonRenderer_->SetAlpha(100);
	}
}


