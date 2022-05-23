#include "Button.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <vector>

Button::Button() 
{
}

Button::~Button() 
{
}

void Button::ButtonInit(std::string _ButtonName, float4 _Size)
{
	// 이름 설정
	ButtonName_ = _ButtonName;

	// 콜리전 설정
	ButtonCol_ = CreateCollision("Button", _Size);
	ButtonCol_->SetPivot(_Size.Half());

	// 최초 상태
	State_ = MOUSE_STATE::MOUSE_OUT;
}

void Button::ButtonUpdate()
{
	MouseInOutCheck();
	UpdateState();
}

void Button::UpdateState()
{
	if (nullptr == ButtonCol_)
	{
		return;
	}

	switch (State_)
	{
	case Button::MOUSE_STATE::MOUSE_IN:
		MouseInUpdate();
		break;
	case Button::MOUSE_STATE::MOUSE_OUT:
		break;
	case Button::MOUSE_STATE::MOUSE_CLICK:
		break;
	default:
		break;
	}

}

void Button::MouseInUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
	{
		ChangeState(MOUSE_STATE::MOUSE_CLICK);
	}

	if (true == GameEngineInput::GetInst()->IsUp(KEY_MOUSE_LEFT))
	{
		ChangeState(MOUSE_STATE::MOUSE_IN);
	}
}

void Button::MouseInOutCheck()
{
	// 마우스와 충돌체크
	std::vector<GameEngineCollision*> MouseColCheck;

	if (true == ButtonCol_->CollisionResult("Mouse", MouseColCheck))
	{
		ChangeState(MOUSE_STATE::MOUSE_IN);
	}
	else
	{
		ChangeState(MOUSE_STATE::MOUSE_OUT);
	}

	MouseColCheck.clear();
}

void Button::ChangeState(MOUSE_STATE _State)
{
	State_ = _State;
}

