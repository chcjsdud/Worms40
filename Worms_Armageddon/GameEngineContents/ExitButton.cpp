#include "ExitButton.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

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

	OnClickButton();
}

void ExitButton::OnClickButton()
{
	if (MOUSE_STATE::MOUSE_CLICK == Button::GetMouseState() && true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
	{
		GameEngineWindow::GetInst().Off();
	}
}

