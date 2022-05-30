#include "ReadyButton.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


ReadyButton::ReadyButton()
	: IsPlayerReady_(false)
	, IsReadyPossible_(false)
{
}

ReadyButton::~ReadyButton()
{
}

void ReadyButton::Start()
{
	Button::ButtonInit("NotReady", float4{ 217,154 }, true);
}

void ReadyButton::Update()
{
	// 마우스 상태 확인 기능 + 경계선 활성화 기능
	Button::ButtonUpdate();

	ButtonNameUpdate();

	// 클릭 시 기능
	OnClickButton();

	IsReadyPossible_ = true;
}

void ReadyButton::OnClickButton()
{
	if (true == IsReadyPossible_ && MOUSE_STATE::MOUSE_CLICK_LEFT == Button::GetMouseState())
	{
		IsPlayerReady_ = !IsPlayerReady_;
	}
}

// 동일한 이미지, 다른 상태를 가진 버튼시 구현
void ReadyButton::ButtonNameUpdate()
{
	if (false == IsPlayerReady_)
	{
		ButtonName_ = "NotReady";
		return;
	}

	ButtonName_ = "Ready";
}
