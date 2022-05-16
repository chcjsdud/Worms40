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
	//�ӽ� ũ�� ����
	BackGround = CreateRendererToScale("MapBooks.bmp", { 1280,720 },1);
	//BackGround->SetImage("MapBooks.bmp");
	float4 BackGroundHalf = BackGround->GetScale().Half();
	BackGround->SetPivot(BackGroundHalf);

	//�ȼ��浹 üũ�� �̹���
	ColImage = CreateRendererToScale("MapBooks_Ground.bmp", { 1280,720 }, 0);
	float4 ColImageHalf = ColImage->GetScale().Half();
	ColImage->SetPivot(ColImageHalf);


	//�ȼ�Ȯ�ο� �ӽ� Ű
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
