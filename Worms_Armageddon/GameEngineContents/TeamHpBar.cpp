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

void TeamHpBar::InitTeamHpBar(int _TeamIndex)
{
	TeamNameRenderer_ = CreateRenderer("BottomNameTag" + std::to_string(_TeamIndex) + ".bmp", (int)RenderOrder::UI);
	TeamFlagRenderer_ = CreateRenderer("BottomFlagKOR.bmp", (int)RenderOrder::UI);
	TeamHpBarRenderer_ = CreateRenderer("BottomHPbar" + std::to_string(_TeamIndex) + ".bmp", (int)RenderOrder::UI);

	TeamNameRenderer_->CameraEffectOff();
	TeamFlagRenderer_->CameraEffectOff();
	TeamHpBarRenderer_->CameraEffectOff();

	TeamNameRenderer_->SetPivot({ -(TeamNameRenderer_->GetScale().Half().x + TeamFlagRenderer_->GetScale().Half().x), 0 });
	TeamHpBarRenderer_->SetPivot({ (TeamHpBarRenderer_->GetScale().Half().x + TeamFlagRenderer_->GetScale().Half().x), 0 });
}

void TeamHpBar::Start()
{

}

void TeamHpBar::Update()
{

}