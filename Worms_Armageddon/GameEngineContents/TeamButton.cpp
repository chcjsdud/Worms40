#include "TeamButton.h"
#include "TeamHandicapButton.h"

TeamButton::TeamButton()
	: IsSelected_(false)
	, IsSwaping_(false)
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
	HandicapButton_ = GetLevel()->CreateActor<TeamHandicapButton>((int)ActorGroup::UI);
	HandicapButton_->ButtonInit("HandicapNormal", { 30, 30 }, true);
	HandicapButton_->Off();

	ColorButton_ = GetLevel()->CreateActor<TeamColorButton>((int)ActorGroup::UI);
	ColorButton_->ButtonInit("BlueTeam", { 30, 30 }, true);
	ColorButton_->Off();

	NumButton_ = GetLevel()->CreateActor<TeamNumButton>((int)ActorGroup::UI);
	NumButton_->ButtonInit("1", { 120, 30 }, true);
	NumButton_->Off();
}

void TeamButton::SetAllButtonPosition(const float4 _Value)
{
	SetPosition(_Value);
	HandicapButton_->SetPosition(_Value + float4{ 300, 0 });
	ColorButton_->SetPosition(_Value + float4{ 330, 0 });
	NumButton_->SetPosition(_Value + float4{ 360, 0 });
}

void TeamButton::Start()
{
	ButtonInit("1-UP", float4{ 120 , 30 });

	
}

void TeamButton::Update()
{
	OnClickButton();
	TeamSettingActivate();
	Button::ButtonUpdate();
}

void TeamButton::OnClickButton()
{
	// 위로 올리고 아래로 내리고
	if (Button::MOUSE_STATE::MOUSE_CLICK_LEFT == Button::GetMouseState())
	{
		IsSelected_ = !IsSelected_;
		IsSwaping_ = true;
	}
}

void TeamButton::TeamSettingActivate()
{
	if (false == IsSwaping_)
	{
		return;
	}

	if (false == IsSelected_)
	{
		HandicapButton_->Off();
		ColorButton_->Off();
		NumButton_->Off();
	}
	else
	{
		HandicapButton_->On();
		ColorButton_->On();
		NumButton_->On();
		ColorButton_->SetColor(TeamColor::Red);
		NumButton_->SetTeamNumber(3);
	}

	IsSwaping_ = false;

}

