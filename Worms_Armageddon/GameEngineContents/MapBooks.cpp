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

	// 충돌판정 렌더러?
	ColMapRenderer_= CreateRendererToScale(IMG_MAPBOOKS_GROUND, { 5000.0f * 0.4f, 3200.0 * 0.4f }, (int)RenderOrder::BackGround_2);
	ColMapHalf = ColMapRenderer_->GetScale().Half();
	ColMapRenderer_->SetPivot(ColMapHalf);

	// 맵 렌더러
	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { SCALE_MAPBOOKS_X, SCALE_MAPBOOKS_Y }, (int)RenderOrder::BackGround_2);
	GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);



	// 배경 이미지
	LargeCloudActor_ = GetLevel()->CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200.0f,200.0f });
	SmallCloudActor_ = GetLevel()->CreateActor<SmallCloud>();
	SmallCloudActor_->SetPosition({ 250.0f,200.0f });

	// 물 이미지
	WaterActor_ = GetLevel()->CreateActor<Water>();
	WaterActor_->SetPosition({ SCALE_CAMERA_MAPMOOKS_X / 2, SCALE_CAMERA_MAPMOOKS_Y - 50});


	// 플레이어 포지션 설정
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