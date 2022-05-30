#include "TeamColorButton.h"


TeamColorButton::TeamColorButton()
	: TeamColor_(TeamColor::Red)
{
}

TeamColorButton::~TeamColorButton() 
{
}

void TeamColorButton::Start()
{
}

void TeamColorButton::Update()
{
	OnClickButton();
	TeamColorNameUpdate();
	Button::ButtonUpdate();

}

void TeamColorButton::OnClickButton()
{
	if (MOUSE_STATE::MOUSE_CLICK_LEFT == Button::GetMouseState())
	{
		int NextColor = static_cast<int>(TeamColor_) + 1;
		if (NextColor >= static_cast<int>(TeamColor::Max))
		{
			NextColor = 0;
		}
		TeamColor_ = static_cast<TeamColor>(NextColor);
	}

	if (MOUSE_STATE::MOUSE_CLICK_RIGHT == Button::GetMouseState())
	{
		int NextColor = static_cast<int>(TeamColor_) - 1;
		if (NextColor < static_cast<int>(TeamColor::Red))
		{
			NextColor = static_cast<int>(TeamColor::Max) - 1;
		}
		TeamColor_ = static_cast<TeamColor>(NextColor);
	}
}

void TeamColorButton::TeamColorNameUpdate()
{
	switch (TeamColor_)
	{
	case TeamColor::Red:
		ButtonName_ = "RedTeam";
		break;
	case TeamColor::Blue:
		ButtonName_ = "BlueTeam";
		break;
	case TeamColor::Green:
		ButtonName_ = "GreenTeam";
		break;
	case TeamColor::Yellow:
		ButtonName_ = "YellowTeam";
		break;
	case TeamColor::Pink:
		ButtonName_ = "PinkTeam";
		break;
	case TeamColor::Mint:
		ButtonName_ = "MintTeam";
		break;
	case TeamColor::Max:
		break;
	default:
		break;
	}
}