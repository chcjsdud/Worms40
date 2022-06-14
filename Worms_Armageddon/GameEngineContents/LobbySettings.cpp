#include "LobbySettings.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>

LobbySettings::LobbySettings() 
	: BoxRenderer_(nullptr)
	, TurnTimeButtonPtr_(nullptr)
{
}

LobbySettings::~LobbySettings() 
{
}

void LobbySettings::Start()
{
	BoxRenderer_ = CreateRenderer("LobbySettings.bmp", (int)RenderOrder::BackGround_1);
	BoxRenderer_->SetScale({ 688, 208 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

	TurnTimeButtonPtr_ = GetLevel()->CreateActor<TurnTimeButton>((int)ActorGroup::UI);
	TurnTimeButtonPtr_->SetScale({ 70, 70 });
	TurnTimeButtonPtr_->SetPosition({585, 388});
}

void LobbySettings::Update()
{
}

