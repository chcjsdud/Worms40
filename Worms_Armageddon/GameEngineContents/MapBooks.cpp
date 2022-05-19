#include "MapBooks.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

MapBooks::MapBooks() 
{
}

MapBooks::~MapBooks() 
{
}

void MapBooks::Start()
{
	float4 GroundHalf = float4::ZERO;

	BackGround_ = CreateRenderer(IMG_GRADIENT, (int)RenderOrder::BackGround_0);
	GroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(GroundHalf);

	Ground_ = CreateRenderer(IMG_MAPBOOKS, (int)RenderOrder::BackGround_2);
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find("IMG_MAPBOOKS_GROUND");
}

void MapBooks::Update()
{

}