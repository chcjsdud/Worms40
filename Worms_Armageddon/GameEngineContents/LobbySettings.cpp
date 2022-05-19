#include "LobbySettings.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

LobbySettings::LobbySettings() 
	: BoxRenderer_(nullptr)
{
}

LobbySettings::~LobbySettings() 
{
}

void LobbySettings::Start()
{
	BoxRenderer_ = CreateRenderer("LobbySettings.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({ 688, 208 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void LobbySettings::Update()
{
}

