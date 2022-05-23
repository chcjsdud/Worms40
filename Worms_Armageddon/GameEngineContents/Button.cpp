#include "Button.h"
#include <GameEngine/GameEngineCollision.h>
#include <vector>

Button::Button() 
{
}

Button::~Button() 
{
}

void Button::ButtonInit(std::string _ButtonName, float4 _Size)
{
	// �̸� ����
	ButtonName_ = _ButtonName;

	// �ݸ��� ����
	ButtonCol_ = CreateCollision("Button", _Size);
	ButtonCol_->SetPivot(_Size.Half());

	// ���� ����
	State_ = MOUSE_STATE::MOUSE_OUT;
}

void Button::ButtonUpdate()
{
	UpdateState();
}

void Button::UpdateState()
{
	if (nullptr == ButtonCol_)
	{
		return;
	}

	// ���콺�� �浹üũ
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

