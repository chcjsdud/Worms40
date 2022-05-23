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

	BackGround_ = CreateRendererToScale(IMG_GRADIENT,{3840,1392}, (int)RenderOrder::BackGround_0);
	GroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(GroundHalf);
	//배경색은 카메라영향을 받지 않게.
	BackGround_->CameraEffectOff();

	Ground_ = CreateRenderer(IMG_MAPBOOKS, (int)RenderOrder::BackGround_2);
	GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);
}

void MapBooks::Update()
{

}