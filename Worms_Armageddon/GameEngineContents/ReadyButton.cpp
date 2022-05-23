#include "ReadyButton.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>


ReadyButton::ReadyButton() 
	: IsPlayerReady_(false)
	, IsMouseIn_(false)
	, ButtonRenderer_(nullptr)
{
}

ReadyButton::~ReadyButton() 
{
}

void ReadyButton::Start()
{
	ButtonRenderer_ = CreateRenderer("Btn_NotReady_Idle.bmp", (int)RenderOrder::UI);
	ButtonRenderer_->SetScale({ 217, 154 });
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());

	// �ݸ��� ����
	ButtonInit("NotReady", ButtonRenderer_->GetScale());

}

void ReadyButton::Update()
{
	// Button Ŭ���� ��ӹ޾��� ��
	// ���콺�� ���� Ȯ�� ����
	Button::ButtonUpdate();
	MouseState_ = GetMouseState();

	ButtonNameUpdate();
	ButtonBorder();
	OnClickButton();
}

void ReadyButton::OnClickButton()
{
	if (MouseState_ == MOUSE_STATE::MOUSE_CLICK)
	{
		IsPlayerReady_ = !IsPlayerReady_;
	}
}

void ReadyButton::ButtonBorder()
{
	if (MouseState_ == MOUSE_STATE::MOUSE_OUT)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_Idle.bmp");
	}

	// ���콺 ����
	else if (MouseState_ == MOUSE_STATE::MOUSE_IN)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_MouseOver.bmp");
	}
}

void ReadyButton::ButtonNameUpdate()
{
	if (false == IsPlayerReady_)
	{
		ButtonName_ = "NotReady";
		return;
	}
	
	ButtonName_ = "Ready";
}
