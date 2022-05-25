#include "TeamButton.h"

//const float4 BTN1_UP_POS = float4{ 265, 20 };
//const float4 BTN2_UP_POS = float4{ 265, 50 };
//const float4 BTN3_UP_POS = float4{ 265, 80 };
//const float4 BTN4_UP_POS = float4{ 265, 110 };
//const float4 BTN5_UP_POS = float4{ 265, 140 };
//
//const float4 BTN1_DOWN_POS = float4{ 265, 300 };
//const float4 BTN2_DOWN_POS = float4{ 265, 330 };
//const float4 BTN3_DOWN_POS = float4{ 265, 360 };
//const float4 BTN4_DOWN_POS = float4{ 265, 390 };
//const float4 BTN5_DOWN_POS = float4{ 265, 420 };

TeamButton::TeamButton()
	: IsSelected_(false)
{
}

TeamButton::~TeamButton() 
{
}

void TeamButton::SetButton(int _BtnNum)
{
	std::string BtnNum = std::to_string(_BtnNum);
	ButtonInit(BtnNum + "-UP", float4{ 120, 32 });
}

void TeamButton::Start()
{
	ButtonInit("1-UP", float4{ 120 , 30 });
}

void TeamButton::Update()
{
	Button::ButtonUpdate();
	OnClickButton();
}

void TeamButton::OnClickButton()
{
	// 위로 올리고 아래로 내리고
	if (Button::MOUSE_STATE::MOUSE_CLICK == Button::GetMouseState())
	{
		IsSelected_ = !IsSelected_;
	}
}

