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

	// ���õ� �� ����-> ������ ��ư�� Ȱ��ȭ
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
	// ���� �ø��� �Ʒ��� ������
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

	// ��ư ���� ���� �� Ȱ��ȭ

}

