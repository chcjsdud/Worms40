#include "Foom.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>

Foom::Foom() 
{
}

Foom::~Foom() 
{
}

void Foom::Start()
{
}

void Foom::Update()
{
	FxOffUpdate();

	switch (FxPhase_)
	{
	case 0:
	{
		if (false == IsStartFx_)
		{
			FxPlay(FxPlayList::Circle50);
			FxPlay(FxPlayList::Foom);
			FxPlay(FxPlayList::Elipse50);
			IsStartFx_ = true;
		}

		NextFxPhase(1.f);
		//FxPhase_ = 0;
	}
	break;
	default:
		EffectDeath();
		break;
	}
}