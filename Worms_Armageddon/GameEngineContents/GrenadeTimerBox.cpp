#include "GrenadeTimerBox.h"
#include "Enums.h"

GrenadeTimerBox::GrenadeTimerBox()
	:
	TimerFont_(nullptr),
	TimerState_(GrenadeTimerState::Timer),
	TimerBox_(nullptr),
	Timer_(5),
	StateTimer_(0)
{
}

GrenadeTimerBox::~GrenadeTimerBox()
{
}

void GrenadeTimerBox::Start()
{

}

void GrenadeTimerBox::Update()
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


void GrenadeTimerBox::TimerBoxSetPosition(float4 _Pos)
{
	this->SetPosition(_Pos);
	TimerFont_->SetPosition(_Pos);
}

void GrenadeTimerBox::SetBoxBorder()
{
	TimerBox_->SetImage("GrenadeBoxBorder.bmp");
}

void GrenadeTimerBox::SetBoxThin()
{
	TimerBox_->SetImage("GrenadeBox.bmp");

}

void GrenadeTimerBox::CreateGrenadeTimerBox(FONT_COLOR _FontColor)
{

	TimerBox_ = CreateRenderer("GrenadeBox.bmp", static_cast<int>(RenderOrder::UI));
	TimerFont_ = GetLevel()->CreateActor<Font>();
	FontColor_ = _FontColor;
	TimerFont_->GameContentCreateNumberFont(5, { 0,0 }, FontColor_);
}
