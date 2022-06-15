#include "TimerBox.h"
#include "Enums.h"

TimerBox::TimerBox()
	:
	TimerFont_(nullptr),
	TimerState_(GrenadeTimerState::Timer),
	TimerBox_(nullptr),
	Timer_(5),
	StateTimer_(0)
{
}

TimerBox::~TimerBox()
{
}

void TimerBox::Start()
{

}

void TimerBox::Update()
{
	if (TimerBox_ != nullptr)
	{
		switch (TimerState_)
		{
		case GrenadeTimerState::Timer:
			if (GetAccTime() >= 1.0f)
			{
				Timer_ -= 1;
				TimerState_ = GrenadeTimerState::ChangeFont;
				break;
			}

			break;
		case GrenadeTimerState::ChangeFont:

			TimerFont_->GameContentChangeNumberFont(Timer_, { 0,0 }, FontColor_);
			ReSetAccTime();
			SetBoxBorder();
			TimerState_ = GrenadeTimerState::BorderChange;

			break;

		case GrenadeTimerState::BorderChange:


			if (GetAccTime() >= 0.3f)
			{
				SetBoxThin();
				TimerState_ = GrenadeTimerState::Timer;
				break;

			}
			break;

		default:
			break;
		}
	}

}


void TimerBox::TimerBoxSetPosition(float4 _Pos)
{
	this->SetPosition(_Pos);
	TimerFont_->SetPosition(_Pos);
}

void TimerBox::SetBoxBorder()
{

	TimerBox_->SetImage("GrenadeBoxBorder.bmp");

	if (Timer_ >= 10)
	{
		TimerBox_->SetScale({ 24, 18 });
	}
}

void TimerBox::SetBoxThin()
{

	TimerBox_->SetImage("GrenadeBox.bmp");

	if (Timer_ >= 10)
	{
		TimerBox_->SetScale({ 24, 18 });
	}
}


void TimerBox::DeleteGrenadeBox()
{
	TimerFont_->Death();
	TimerBox_->Death();
	this->Death();
}

void TimerBox::CreateTimerBox(FONT_COLOR _FontColor, int _Time)
{

	TimerBox_ = CreateRenderer("GrenadeBox.bmp", static_cast<int>(RenderOrder::UI));
	TimerFont_ = GetLevel()->CreateActor<Font>();
	FontColor_ = _FontColor;
	Timer_ = _Time;

	if (_Time >= 10)
	{
		TimerBox_->SetScale({24, 18});
	}

	TimerFont_->GameContentCreateNumberFont(Timer_, { 0,0 }, FontColor_);
}
