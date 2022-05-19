#include "RollingStar.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

RollingStar::RollingStar() 
	: Renderer_(nullptr)
{
}

RollingStar::~RollingStar() 
{
}

void RollingStar::Start()
{
	Renderer_ = CreateRenderer(static_cast<int>(RenderOrder::BackGround_1));
	Renderer_->SetScale({ 100, 100 });
	Renderer_->SetTransColor(RGB(0, 0, 0));
	Renderer_->CreateAnimation("stars.bmp", "RollingStar", 0, 127, 0.05f, true, true);
	Renderer_->ChangeAnimation("RollingStar");
}

void RollingStar::Update()
{
}

