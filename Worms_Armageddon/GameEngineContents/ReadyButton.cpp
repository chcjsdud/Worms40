#include "ReadyButton.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


ReadyButton::ReadyButton()
	: IsPlayerReady_(false)
	, MouseState_(MOUSE_STATE::MOUSE_OUT)
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
	// ���콺 ���� Ȯ�� ��� + ��輱 Ȱ��ȭ ���
	Button::ButtonUpdate();

	// ���콺 ���� Ȯ�� ���
	MouseState_ = Button::GetMouseState();

	ButtonNameUpdate();

	// Ŭ�� �� ���
	OnClickButton();

	IsReadyPossible_ = true;
}

void ReadyButton::OnClickButton()
{
	if (true == IsReadyPossible_ && MouseState_ == MOUSE_STATE::MOUSE_CLICK)
	{
		IsPlayerReady_ = !IsPlayerReady_;
	}
}

// ������ �̹���, �ٸ� ���¸� ���� ��ư�� ����
void ReadyButton::ButtonNameUpdate()
{
	if (false == IsPlayerReady_)
	{
		ButtonName_ = "NotReady";
		return;
	}

	ButtonName_ = "Ready";
}
