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
	for (GameEngineRenderer* FxOb : AllFxObject_)
	{
		if (true == FxOb->IsEndAnimation())
		{
			FxOb->Off();
			++FxOffCnt_;
		}
	}

	switch (FxOrder_)
	{
	case 0:
	{
		if (false == IsStartFx_)
		{
			{
				GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx);
				FxObject->CreateAnimation(IMG_FX_EXFOOM, ANIM_NAME_FX_EXFOOM, 0, 19, 0.1f, false);
				FxObject->ChangeAnimation(ANIM_NAME_FX_EXFOOM);
				AllFxObject_.push_back(FxObject);
			}

			IsStartFx_ = true;
		}

		if (1.f < GetAccTime())
		{
			if (true == IsStartFx_)
			{
				IsStartFx_ = false;
				FxOrder_ += 1;
			}
		}
	}
	break;
	case 1:
	{
		if (false == IsStartFx_)
		{
			{
				GameEngineRenderer* FxObject = CreateRenderer((int)RenderOrder::Front_Fx);
				FxObject->CreateAnimation(IMG_FX_CIRCLE50, ANIM_NAME_FX_CIRCLE50, 0, 7, 0.1f, false);
				FxObject->ChangeAnimation(ANIM_NAME_FX_CIRCLE50);
				AllFxObject_.push_back(FxObject);
			}

			IsStartFx_ = true;
		}

		if (1.f < GetAccTime())
		{
			if (true == IsStartFx_)
			{
				IsStartFx_ = false;
				FxOrder_ += 1;
			}
		}
	}
		break;
	default:
		if (FxOffCnt_ == AllFxObject_.size())
		{
			for (GameEngineRenderer* FxOb : AllFxObject_)
			{
				FxOb->Death();
			}
			AllFxObject_.clear();
		}
		break;
	}
}