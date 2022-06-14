#pragma once
#include "HpBar.h"
#include "Enums.h"

HpBar::HpBar()
	:
	HpBar_(nullptr),
	HpFont_(nullptr),
	FontColor_(FONT_COLOR::White),
	Hp_(100)
{
}

HpBar::~HpBar()
{
}

void HpBar::Start()
{
	HpBar_ = CreateRenderer("WormHP.bmp", static_cast<int>(RenderOrder::HpBar));
	HpFont_ = GetLevel()->CreateActor<Font>();
	HpFont_->GameContentCreateNumberFont(0, { 0,0 }, FONT_COLOR::White);
}

void HpBar::Update()
{
}

void HpBar::ChangeHpBarFont(int _Num)
{
	HpFont_->GameContentChangeNumberFont(_Num, {0,0}, FontColor_);
}

void HpBar::SetFontColor(FONT_COLOR _FontColor)
{
	FontColor_ = _FontColor;
}


void HpBar::HpBarSetPosition(float4 _Pos)
{
	this->SetPosition(_Pos);
	HpFont_->SetPosition(_Pos);
}
