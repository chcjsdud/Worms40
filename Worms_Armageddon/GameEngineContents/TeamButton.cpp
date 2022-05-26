#include "TeamButton.h"
#include "TeamColorButton.h"

#include "Enums.h"

TeamButton::TeamButton()
	: IsSelected_(false)
{
}

TeamButton::~TeamButton() 
{
}

void TeamButton::SetButton(int _BtnNum)
{
	ButtonIndex_ = _BtnNum;
	std::string BtnNum = std::to_string(_BtnNum);
	ButtonInit(BtnNum + "-UP", float4{ 120, 32 });

	// 선택된 팀 상태-> 오른쪽 버튼들 활성화
	ColorButton_ = GetLevel()->CreateActor<TeamColorButton>(0);
	ColorButton_->ButtonInit("RedTeam", { 40, 40 }, true);
	ColorButton_->SetPosition(GetPosition());
}

void TeamButton::SetAllButtonPosition(const float4 _Value)
{
	SetPosition(_Value);
	ColorButton_->SetPosition(_Value + float4{ 200, 0 });
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

void TeamButton::TeamSettingActivate()
{
	if (false == IsSelected_)
	{
		return;
	}

	// 버튼 옆에 세팅 을 활성화

}

