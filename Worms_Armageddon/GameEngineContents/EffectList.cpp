#include "EffectManager.h"
#include <GameEngine/GameEngineRenderer.h>

void EffectManager::PlayFoom()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx);
	FxObject->CreateAnimation(IMG_FX_EXFOOM, ANIM_NAME_FX_EXFOOM, 0, 19, 0.1f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_EXFOOM);
	AllFxObject_.push_back(FxObject);
}

void EffectManager::PlayCircle50()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx);
	FxObject->CreateAnimation(IMG_FX_CIRCLE50, ANIM_NAME_FX_CIRCLE50, 0, 7, 0.1f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_CIRCLE50);
	AllFxObject_.push_back(FxObject);
}