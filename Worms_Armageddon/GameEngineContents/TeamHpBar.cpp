#include "TeamHpBar.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

TeamHpBar::TeamHpBar()
{
}

TeamHpBar::~TeamHpBar() 
{
}

void TeamHpBar::InitTeamHpBar(int _TeamIndex, int _MemberNum)
{
	TeamNameRenderer_ = CreateRenderer("BottomNameTag" + std::to_string(_TeamIndex) + ".bmp", (int)RenderOrder::UI_2);
	TeamFlagRenderer_ = CreateRenderer("BottomFlagKOR.bmp", (int)RenderOrder::UI_2);
	TeamHpBarRenderer_ = CreateRenderer("BottomHPbar" + std::to_string(_TeamIndex) + ".bmp", (int)RenderOrder::UI_2);

	TeamNameRenderer_->CameraEffectOff();
	TeamFlagRenderer_->CameraEffectOff();
	TeamHpBarRenderer_->CameraEffectOff();

	TeamNameRenderer_->SetPivot({ -(2 + TeamNameRenderer_->GetScale().Half().x + TeamFlagRenderer_->GetScale().Half().x), 0 });
	TeamHpBarRenderer_->SetPivot({ (2 + TeamHpBarRenderer_->GetScale().Half().x + TeamFlagRenderer_->GetScale().Half().x), 0 });

	TotalHp_ = _MemberNum * 100.0f;
	CurrentHp_ = TotalHp_;
	BarWidth_ = TeamHpBarRenderer_->GetScale().x;
	BarPivot_ = TeamHpBarRenderer_->GetPivot();
}

void TeamHpBar::DecreaseInit(int _Damage)
{
	TargetHp_ = static_cast<float>(_Damage);
}

bool TeamHpBar::Decrease()
{
	if (CurrentHp_ <= TargetHp_)
	{
		CurrentHp_ = TargetHp_;
		return true;
	}

	CurrentHp_ -= 1 * GameEngineTime::GetDeltaTime() * 100.0f;
	// 체력바 렌더러 줄이기
	float Ratio = CurrentHp_ / TotalHp_;
	TeamHpBarRenderer_->SetScale({ BarWidth_ * Ratio, TeamHpBarRenderer_->GetScale().y });

	float PivotX = (BarWidth_ - BarWidth_ * Ratio) / 2;
	TeamHpBarRenderer_->SetPivot({BarPivot_.x - PivotX, BarPivot_.y });

	return false;
}

void TeamHpBar::Start()
{

}

void TeamHpBar::Update()
{
	UIMaster::UpdateState();
}