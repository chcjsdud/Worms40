#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineDebug.h>
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
	// TODO::배경 그라디언트는 맵의 크기만큼 스케일 해야할듯?
	BackGround_ = CreateRendererToScale(IMG_GRADIENT, { SCALE_GRADIENT_X, SCALE_GRADIENT_Y }, 0);
	float4 BackGroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(BackGroundHalf);


	//임시 크기 설정
	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { SCALE_MAPBOOKS_X, SCALE_MAPBOOKS_Y },2);
	//BackGround->SetImage("MapBooks.bmp");
	float4 GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	//픽셀충돌 체크할 이미지
	ColImage_ = CreateRendererToScale(IMG_MAPBOOKS_GROUND, { SCALE_MAPBOOKS_GROUND_X, SCALE_MAPBOOKS_GROUND_Y }, 1);
	float4 ColImageHalf = ColImage_->GetScale().Half();
	ColImage_->SetPivot(ColImageHalf);


	//픽셀확인용 임시 키
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_PIXELMODE, '0');
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
	if (GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PIXELMODE))
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
