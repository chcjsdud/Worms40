#include "TestMap.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

TestMap::TestMap() :
	ChangeMode(false)
{
}

TestMap::~TestMap() 
{
}

void TestMap::Start()
{
	//임시 크기 설정
	BackGround = CreateRendererToScale("MapBooks.bmp", { 1280,720 },1);
	//BackGround->SetImage("MapBooks.bmp");
	float4 BackGroundHalf = BackGround->GetScale().Half();
	BackGround->SetPivot(BackGroundHalf);

	//픽셀충돌 체크할 이미지
	ColImage = CreateRendererToScale("MapBooks_Ground.bmp", { 1280,720 }, 0);
	float4 ColImageHalf = ColImage->GetScale().Half();
	ColImage->SetPivot(ColImageHalf);


	//픽셀확인용 임시 키
	GameEngineInput::GetInst()->CreateKey("ChangePixelMode", '0');
}

void TestMap::Update()
{
	ChangePixelMode();
}

void TestMap::Render()
{

}



void TestMap::ChangePixelMode()
{
	if (GameEngineInput::GetInst()->IsDown("ChangePixelMode"))
	{
		if (false == ChangeMode)
		{
			BackGround->Off();
			ChangeMode = true;
		}
		else
		{
			BackGround->On();
			ChangeMode = false;
		}
	}
}
