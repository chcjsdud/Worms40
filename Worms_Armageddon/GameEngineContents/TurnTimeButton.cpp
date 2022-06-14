#include "TurnTimeButton.h"


TurnTimeButton::TurnTimeButton() 
	:
	ButtonRenderer_(nullptr)
{
	TurnTimes_ = {15, 20, 30, 45, 60, 90, 999};
	TurnTimesIdx_ = 3;
	CurrentTurnTime_ = TurnTimes_[TurnTimesIdx_];
}

TurnTimeButton::~TurnTimeButton() 
{
}

void TurnTimeButton::Start()
{
	ButtonInit(TurnTimeToString(), {70, 70}, true);
	
}

void TurnTimeButton::Update()
{
	OnClickButton();
	ButtonNameUpdate();
	Button::ButtonUpdate();
}

void TurnTimeButton::OnClickButton()
{
	if (MOUSE_STATE::MOUSE_CLICK_LEFT == Button::GetMouseState())
	{
		TurnTimesIdx_++;
		if (TurnTimes_.size() <= TurnTimesIdx_)
		{
			TurnTimesIdx_ = 0;
		}
		CurrentTurnTime_ = TurnTimes_[TurnTimesIdx_];
		return;
	}

	if (MOUSE_STATE::MOUSE_CLICK_RIGHT == Button::GetMouseState())
	{
		TurnTimesIdx_--;
		if (0 > TurnTimesIdx_)
		{
			TurnTimesIdx_ = static_cast<int>(TurnTimes_.size()) - 1;
		}
		CurrentTurnTime_ = TurnTimes_[TurnTimesIdx_];
		return;
	}
}

std::string TurnTimeButton::TurnTimeToString()
{
	if (999 != CurrentTurnTime_)
	{
		return std::to_string(CurrentTurnTime_);
	}
	else
	{
		return "INF";
	}
}

void TurnTimeButton::ButtonNameUpdate()
{
	ButtonName_ = TurnTimeToString();
}
