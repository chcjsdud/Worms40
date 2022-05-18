#include "LargeCloud.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>

LargeCloud::LargeCloud() 
{
}

LargeCloud::~LargeCloud() 
{
}

void LargeCloud::Start()
{	


	CloudRenderer_ = CreateRenderer(10000);
	CloudRenderer_->CreateAnimation("cloudl.bmp", "CloudAni", 0, 19, 0.05f, true,true);
	CloudRenderer_->ChangeAnimation("CloudAni");

}

void LargeCloud::Update()
{
	//SetMove()
}

void LargeCloud::Render()
{
}
