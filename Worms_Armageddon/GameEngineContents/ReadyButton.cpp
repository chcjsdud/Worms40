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
	ButtonInit("NotReady", "Btn_NotReady_Idle.bmp");

	GameEngineRenderer* ButtonRenderer = Button::GetRenderer();
	GameEngineCollision* ButtonCollision = Button::GetCollision();
	
	ButtonRenderer->SetScale({ 217, 154 });
	ButtonRenderer->SetPivot(ButtonRenderer->GetScale().Half());

	ButtonCollision->SetScale(ButtonRenderer->GetScale());
	ButtonCollision->SetPivot(ButtonRenderer->GetScale().Half());
}

void ReadyButton::Update()
{
	// Button 클래스 상속받았을 때
	// 마우스의 상태 확인 가능
	Button::ButtonUpdate();
	MouseState_ = GetMouseState();

	ButtonNameUpdate();

	// 클릭 시 기능
	OnClickButton();
}

void ReadyButton::OnClickButton()
{
	if (true == IsReadyPossible_ && MouseState_ == MOUSE_STATE::MOUSE_CLICK)
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
