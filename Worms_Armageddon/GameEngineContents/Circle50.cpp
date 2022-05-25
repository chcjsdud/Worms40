#include "Circle50.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>

Circle50::Circle50() 
{
}

Circle50::~Circle50() 
{
}

void Circle50::Start()
{
	FxObject_ = CreateRenderer((int)RenderOrder::Front_Fx);
	FxObject_->CreateAnimation(IMG_FX_CIRCLE50, ANIM_NAME_FX_CIRCLE50, 0, 7, 0.1f, false);
	FxObject_->ChangeAnimation(ANIM_NAME_FX_CIRCLE50);
}

void Circle50::Update()
{
	if (true == FxObject_->IsEndAnimation())
	{
		Death();
	}
}