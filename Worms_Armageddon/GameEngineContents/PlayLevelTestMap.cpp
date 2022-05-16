#include "PlayLevelTestMap.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

PlayLevelTestMap::PlayLevelTestMap() :
	ChangeMode_(false)
{
}

PlayLevelTestMap::~PlayLevelTestMap() 
{
}

void PlayLevelTestMap::Start()
{
	BackGround_ = CreateRendererToScale("gradient.bmp", { 1280,960 }, 0);
	float4 BackGroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(BackGroundHalf);


	//임시 크기 설정
	Ground_ = CreateRendererToScale("MapBooks.bmp", { 1280,960 },2);
	//BackGround->SetImage("MapBooks.bmp");
	float4 GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	//픽셀충돌 체크할 이미지
	ColImage_ = CreateRendererToScale("MapBooks_Ground.bmp", { 1280,960 }, 1);
	float4 ColImageHalf = ColImage_->GetScale().Half();
	ColImage_->SetPivot(ColImageHalf);


	//픽셀확인용 임시 키
	GameEngineInput::GetInst()->CreateKey("ChangePixelMode", '0');
}

void PlayLevelTestMap::Update()
{
	ChangePixelMode();
}

void PlayLevelTestMap::Render()
{

}



void PlayLevelTestMap::ChangePixelMode()
{
	if (GameEngineInput::GetInst()->IsDown("ChangePixelMode"))
	{
		if (false == ChangeMode_)
		{
			Ground_->Off();
			ChangeMode_ = true;
		}
		else
		{
			Ground_->On();
			ChangeMode_ = false;
		}
	}
}
