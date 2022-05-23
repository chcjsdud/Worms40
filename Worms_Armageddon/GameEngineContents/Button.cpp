#include "Button.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <vector>

#include "Enums.h"

Button::Button() 
{
}

Button::~Button() 
{
}

void Button::ButtonInit(const std::string _ButtonName, const std::string _ImageName)
{
	// �̸� ����
	ButtonName_ = _ButtonName;

	// ������ ����
	ButtonRenderer_ = CreateRenderer(_ImageName, static_cast<int>(RenderOrder::UI));

	// �ݸ��� ����
	ButtonCol_ = CreateCollision(COL_GROUP_BUTTON, ButtonRenderer_->GetScale());

	// ���� ����
	MouseState_ = MOUSE_STATE::MOUSE_OUT;
}

void Button::ButtonUpdate()
{
	MouseInOutCheck();
	UpdateState();
	ButtonBorderEffect();
}

void Button::UpdateState()
{
	if (nullptr == ButtonCol_)
	{
		return;
	}

	switch (MouseState_)
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

void Button::ButtonBorderEffect()
{
	if (MouseState_ == MOUSE_STATE::MOUSE_OUT)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_Idle.bmp");
	}

	else if (MouseState_ == MOUSE_STATE::MOUSE_IN)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_MouseOver.bmp");
	}
}

void Button::ChangeState(MOUSE_STATE _MouseState)
{
	MouseState_ = _MouseState;
}

