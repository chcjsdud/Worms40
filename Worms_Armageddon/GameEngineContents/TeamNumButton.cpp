#include "TeamNumButton.h"

TeamNumButton::TeamNumButton() 
	: TeamNum_(3)
{
}

TeamNumButton::~TeamNumButton() 
{
}

void TeamNumButton::Start()
{
}

void TeamNumButton::Update()
{
	OnClickButton();
	SetTeamNumButtonName();
	Button::ButtonUpdate();
}

void TeamNumButton::OnClickButton()
{
	if (MOUSE_STATE::MOUSE_CLICK_LEFT == Button::GetMouseState())
	{
		if (TeamNum_ >= 8)
		{
			return;
		}
		TeamNum_++;
	}

	if (MOUSE_STATE::MOUSE_CLICK_RIGHT == Button::GetMouseState())
	{
		if (TeamNum_ <= 1)
		{
			return;
		}
		TeamNum_--;
	}
}

void TeamNumButton::SetTeamNumButtonName()
{
	ButtonName_ = std::to_string(TeamNum_);
}
