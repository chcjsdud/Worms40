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

	// 콜리전 설정
	ButtonInit("NotReady", ButtonRenderer_->GetScale());

}

void ReadyButton::Update()
{
	// Button 클래스 상속받았을 때
	// 마우스의 상태 확인 가능
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

	// 마우스 들어옴
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
