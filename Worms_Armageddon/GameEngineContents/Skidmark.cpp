#include "Skidmark.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>

Skidmark::Skidmark() 
{
}

Skidmark::~Skidmark() 
{
}

void Skidmark::Start()
{
}

void Skidmark::Update()
{
	FxOffUpdate();

	switch (FxPhase_)
	{
	case 0:
	{
		if (false == IsStartFx_)
		{
			FxPlay(FxPlayList::SupersheepSkid);
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