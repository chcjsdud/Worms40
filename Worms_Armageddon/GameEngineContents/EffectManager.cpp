#include "EffectManager.h"
#include <GameEngine/GameEngineRenderer.h>

EffectManager::EffectManager() 
	: FxOffCnt_(0)
	, FxOrder_(0)
	, IsStartFx_(false)
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


void EffectManager::FxOff()
{

}

//void EffectManager::PlayFx(FxPlayList _Fx)
//{
//	switch (_Fx)
//	{
//	case FxPlayList::Foom:
//		void PlayFoom();
//		break;
//	default:
//		break;
//	}
//}