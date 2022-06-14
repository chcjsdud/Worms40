#include "Button.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <vector>

#include "Enums.h"

Button::Button()
	: ButtonCol_(nullptr)
	, ButtonRenderer_(nullptr)
	, IsBorderEffect_(false)
	, ButtonScale_()
	, MouseState_(MOUSE_STATE::MOUSE_OUT)
	, IsActivated_(true)
{
}

Button::~Button()
{
}

Button& Button::ButtonInit(const std::string _ButtonName, float4 _ButtonScale, bool _IsBorderEffect)
{
	// �̸� ����
	ButtonName_ = _ButtonName;
	ButtonScale_ = _ButtonScale;

	// ������ ����
	std::string ImageName;
	if (true == _IsBorderEffect)
	{
		ImageName = "Btn_" + _ButtonName + "_Idle.bmp";
	}
	else
	{
		ImageName = "Btn_" + _ButtonName + ".bmp";
	}

	ButtonRenderer_ = CreateRenderer(ImageName, static_cast<int>(RenderOrder::UI));
	ButtonRenderer_->SetScale(ButtonScale_);
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());

	// �ݸ��� ����
	ButtonCol_ = CreateCollision(COL_GROUP_BUTTON, ButtonRenderer_->GetScale());
	ButtonCol_->SetScale(ButtonRenderer_->GetScale() - float4{5, 5});
	ButtonCol_->SetPivot(ButtonRenderer_->GetScale().Half());

	// ���� ����
	MouseState_ = MOUSE_STATE::MOUSE_OUT;

	// BorderEffect�޴����� ����
	IsBorderEffect_ = _IsBorderEffect;

	return *this;
}

void Button::ButtonUpdate()
{
	if (false == IsActivated_)
	{
		return;
	}

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
	default:
		break;
	}

}

void Button::MouseInUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
	{
		ChangeState(MOUSE_STATE::MOUSE_CLICK_LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_RIGHT))
	{
		ChangeState(MOUSE_STATE::MOUSE_CLICK_RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsFree(KEY_MOUSE_LEFT) && GameEngineInput::GetInst()->IsFree(KEY_MOUSE_RIGHT))
	{
		ChangeState(MOUSE_STATE::MOUSE_IN);
	}
}

void Button::MouseInOutCheck()
{
	std::vector<GameEngineCollision*> MouseColCheck;

	if (true == ButtonCol_->CollisionResult(COL_GROUP_MOUSE, MouseColCheck))
	{
		ChangeState(MOUSE_STATE::MOUSE_IN);
	}
	else
	{
		ChangeState(MOUSE_STATE::MOUSE_OUT);
	}

	MouseColCheck.clear();
}

// BorderEffect����� �ִ� ��ư�� ���� �̸���
// 'Btn_ButtonName_Idle.bmp' / 'Btn_ButtonName_MouseOver.bmp' �� ������ �����־�� ��
void Button::ButtonBorderEffect()
{
	if (false == IsBorderEffect_)
	{
		return;
	}

	if (MouseState_ == MOUSE_STATE::MOUSE_OUT)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_Idle.bmp");
		ButtonRenderer_->SetScale(ButtonScale_);
	}
	else if (MouseState_ == MOUSE_STATE::MOUSE_IN)
	{
		ButtonRenderer_->SetImage("Btn_" + ButtonName_ + "_MouseOver.bmp");
		ButtonRenderer_->SetScale(ButtonScale_);
	}
}

void Button::ChangeState(MOUSE_STATE _MouseState)
{
	MouseState_ = _MouseState;
}

