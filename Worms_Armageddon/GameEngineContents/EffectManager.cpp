#include "EffectManager.h"
#include <GameEngine/GameEngineRenderer.h>

EffectManager::EffectManager() 
	: FxOffCnt_(0)
	, FxPhase_(0)
	, IsStartFx_(false)
	, IsRepeat_(false)
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


void EffectManager::FxOffUpdate()
{
	for (GameEngineRenderer* FxOb : AllFxObject_)
	{
		if (true == FxOb->IsEndAnimation())
		{
			FxOb->Off();
			++FxOffCnt_;
		}
	}
}

void EffectManager::FxPlay(FxPlayList _Fx)
{
	switch (_Fx)
	{
	case FxPlayList::Foom:
		PlayFoom();
		break;

	case FxPlayList::Circle50:
		PlayCircle50();
		break;

	case FxPlayList::Elipse50:
		PlayElipse50();
		break;

	case FxPlayList::SupersheepSkid:
		SupersheepSkid();
		break;

	default:
		break;
	}
}

void EffectManager::NextFxPhase(float _Time)
{
	if (_Time < GetAccTime())
	{
		if (true == IsStartFx_)
		{
			IsStartFx_ = false;
			FxPhase_ += 1;
		}
	}
}

void EffectManager::EffectDeath()
{
	if (FxOffCnt_ == AllFxObject_.size())
	{
		for (GameEngineRenderer* FxOb : AllFxObject_)
		{
			FxOb->Death();
		}
		AllFxObject_.clear();
	}
}