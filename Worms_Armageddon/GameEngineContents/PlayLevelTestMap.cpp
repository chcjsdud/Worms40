#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

PlayLevelTestMap::PlayLevelTestMap() :
	ChangeMode_(false)
	, BackGround_(nullptr)
	, ColImage_(nullptr)
	, Ground_(nullptr)
	, MidGround_(nullptr)
{
}

PlayLevelTestMap::~PlayLevelTestMap() 
{
}

void PlayLevelTestMap::Start()
{
	BackGround_ = CreateRendererToScale(IMG_GRADIENT, { 1280,960 }, 0);
	float4 BackGroundHalf = BackGround_->GetScale().Half();
	BackGround_->SetPivot(BackGroundHalf);

	MidGround_ = CreateRendererToScale(IMG_MIDGROUND, { 1280,195 }, 0);
	float4 MidGround_Half = MidGround_->GetScale().Half();
	MidGround_->SetPivot({MidGround_Half.x, MidGround_Half.y + 765});

	//임시 크기 설정
	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { 1280,960 },2);
	//BackGround->SetImage("MapBooks.bmp");
	float4 GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	//픽셀충돌 체크할 이미지
	ColImage_ = CreateRendererToScale(IMG_MAPBOOKS_GROUND, { 1280,960 }, 1);
	float4 ColImageHalf = ColImage_->GetScale().Half();
	ColImage_->SetPivot(ColImageHalf);


	//픽셀확인용 임시 키
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_PIXELMODE, '0');

	//다른 액터에 참조하기 위한 액터 등록
	LevelRegist("TestMap");
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
