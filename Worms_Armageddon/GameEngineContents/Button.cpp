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
	, MouseState_(MOUSE_STATE::MOUSE_OUT)
	, IsActivated_(true)
{
}

Button::~Button()
{
}

void Button::ButtonInit(const std::string _ButtonName, float4 _ButtonScale, bool _IsBorderEffect)
{
	// 이름 설정
	ButtonName_ = _ButtonName;
	ButtonScale_ = _ButtonScale;

	// 렌더러 설정
	std::string ImageName = "Btn_" + _ButtonName + "_Idle.bmp";
	ButtonRenderer_ = CreateRenderer(ImageName, static_cast<int>(RenderOrder::UI));
	ButtonRenderer_->SetScale(ButtonScale_);
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());

	// 콜리전 설정
	ButtonCol_ = CreateCollision(COL_GROUP_BUTTON, ButtonRenderer_->GetScale());
	ButtonCol_->SetScale(ButtonRenderer_->GetScale());
	ButtonCol_->SetPivot(ButtonRenderer_->GetScale().Half());

	// 최초 상태
	MouseState_ = MOUSE_STATE::MOUSE_OUT;

	// BorderEffect받는지의 여부
	IsBorderEffect_ = _IsBorderEffect;
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

// BorderEffect기능이 있는 버튼의 파일 이름은
// 'Btn_ButtonName_Idle.bmp' / 'Btn_ButtonName_MouseOver.bmp' 로 형식을 맞춰주어야 함
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

