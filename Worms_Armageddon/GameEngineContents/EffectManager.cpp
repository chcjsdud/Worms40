#include "EffectManager.h"
#include <GameEngine/GameEngineRenderer.h>

EffectManager::EffectManager() 
	: FxOrder_(0)
	, IsStartFx_(false)
	, FxSwitch_(FxSwitch::READY)
	, FxObject_ (nullptr)
{
}

EffectManager::~EffectManager() 
{
}

void EffectManager::Start()
{
	
}

void EffectManager::Update()
{
}