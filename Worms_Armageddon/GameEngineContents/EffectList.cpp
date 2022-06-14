#include "EffectManager.h"
#include <GameEngine/GameEngineRenderer.h>

// 설명 : 단일 이펙트 애니메이션 리스트

void EffectManager::PlayFoom()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx, RenderPivot::CENTER, float4::ZERO, false);
	FxObject->CreateAnimation(IMG_FX_EXFOOM, ANIM_NAME_FX_EXFOOM, 0, 19, 0.04f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_EXFOOM);
	AllFxObject_.push_back(FxObject);
}

void EffectManager::PlayCircle50()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx, RenderPivot::CENTER, float4::ZERO, false);
	FxObject->CreateAnimation(IMG_FX_CIRCLE50, ANIM_NAME_FX_CIRCLE50, 0, 7, 0.04f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_CIRCLE50);
	AllFxObject_.push_back(FxObject);
}

void EffectManager::PlayElipse50()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx, RenderPivot::CENTER, float4::ZERO, false);
	FxObject->CreateAnimation(IMG_FX_ELIPSE50, ANIM_NAME_FX_ELIPSE50, 0, 19, 0.04f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_ELIPSE50);
	AllFxObject_.push_back(FxObject);
}

void EffectManager::SupersheepSkid()
{
	GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx, RenderPivot::CENTER, float4::ZERO, false);
	FxObject->CreateAnimation(IMG_FX_SKIDMARK_SPSHEEP, ANIM_NAME_FX_SKIDMARK_SPSHEEP, 0, 9, 0.1f, false);
	FxObject->ChangeAnimation(ANIM_NAME_FX_SKIDMARK_SPSHEEP);
	AllFxObject_.push_back(FxObject);
}