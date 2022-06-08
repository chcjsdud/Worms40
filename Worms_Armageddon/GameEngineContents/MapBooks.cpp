#include "MapBooks.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>

MapBooks::MapBooks() :
	ShowColMap_(false)
{
}

MapBooks::~MapBooks() 
{
}

void MapBooks::Start()
{
	float4 GroundHalf = float4::ZERO;
	float4 ColMapHalf = float4::ZERO;

	BackGround_ = CreateRendererToScale(IMG_GRADIENT,{3840,1392}, (int)RenderOrder::BackGround_0);
	GroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(GroundHalf);
	
	//배경색은 카메라영향을 받지 않게
	BackGround_->CameraEffectOff();

	ColMapRenderer_= CreateRendererToScale(IMG_MAPBOOKS_GROUND, { 5000.0f * 0.4f, 3200.0 * 0.4f }, (int)RenderOrder::BackGround_2);
	ColMapHalf = ColMapRenderer_->GetScale().Half();
	ColMapRenderer_->SetPivot(ColMapHalf);

	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { SCALE_MAPBOOKS_X, SCALE_MAPBOOKS_Y }, (int)RenderOrder::BackGround_2);
	GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);

	for (int i = 0; i < 8; i++)
	{
		float x = static_cast<float>(430 + i * 50);
		float y = 920.0f;

		ResponPosition_[i] = {x, y};
	}
	


	GameEngineInput::GetInst()->CreateKey("ShowColMap", '0');

}

void MapBooks::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("ShowColMap"))
	{
		if (false == ShowColMap_)
		{
			Ground_->Off();
			ShowColMap_ = true;
		}
		else if (true == ShowColMap_)
		{
			Ground_->On();
			ShowColMap_ = false;
		}
	}
}