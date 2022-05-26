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
			FxPlay(FxPlayList::Foom);
			IsStartFx_ = true;
		}

		NextFxPhase(1.f);
	}
	break;
	case 1:
	{
		if (false == IsStartFx_)
		{
			FxPlay(FxPlayList::Circle50);
			IsStartFx_ = true;
		}

		NextFxPhase(1.f);
	}
		break;
	default:
		EffectDeath();
		break;
	}
}