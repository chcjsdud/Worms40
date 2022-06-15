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

	//박지영 : 경고 수정 작업. double에서 float로 캐스팅
	// 충돌판정 렌더러?
	ColMapRenderer_= CreateRendererToScale(IMG_MAPBOOKS_GROUND, { 5000.0f * 0.4f, 3200.0f * 0.4f }, static_cast<int>(RenderOrder::BackGround_2));
	ColMapHalf = ColMapRenderer_->GetScale().Half();
	ColMapRenderer_->SetPivot(ColMapHalf);

	// 맵 렌더러
	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { static_cast<float>(SCALE_MAPBOOKS_X), static_cast<float>(SCALE_MAPBOOKS_Y )}, static_cast<int>(RenderOrder::BackGround_2));
	GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);



	// 배경 이미지
	{
		LargeCloudActor_[0] = GetLevel()->CreateActor<LargeCloud>();
		LargeCloudActor_[0]->SetPosition({ 100.0f,500.0f });
		LargeCloudActor_[0]->SetSpeed(100.0f);

		LargeCloudActor_[1] = GetLevel()->CreateActor<LargeCloud>();
		LargeCloudActor_[1]->SetPosition({ 30.0f,550.0f });
		LargeCloudActor_[1]->SetSpeed(20.0f);

		LargeCloudActor_[2] = GetLevel()->CreateActor<LargeCloud>();
		LargeCloudActor_[2]->SetPosition({ 500.0f,450.0f });
		LargeCloudActor_[2]->SetSpeed(70.0f);

		LargeCloudActor_[3] = GetLevel()->CreateActor<LargeCloud>();
		LargeCloudActor_[3]->SetPosition({ 900.0f,480.0f });
		LargeCloudActor_[3]->SetSpeed(50.0f);

		MiddleCloudActor_[0] = GetLevel()->CreateActor<MiddleCloud>();
		MiddleCloudActor_[0]->SetPosition({ 1500.0f,470.0f });
		MiddleCloudActor_[0]->SetSpeed(100.0f);

		MiddleCloudActor_[1] = GetLevel()->CreateActor<MiddleCloud>();
		MiddleCloudActor_[1]->SetPosition({ 400.0f,520.0f });
		MiddleCloudActor_[1]->SetSpeed(150.0f);

		MiddleCloudActor_[2] = GetLevel()->CreateActor<MiddleCloud>();
		MiddleCloudActor_[2]->SetPosition({ 620.0f,500.0f });
		MiddleCloudActor_[2]->SetSpeed(20.0f);

		SmallCloudActor_[0] = GetLevel()->CreateActor<SmallCloud>();
		SmallCloudActor_[0]->SetPosition({ 220.0f,510.0f });
		SmallCloudActor_[0]->SetSpeed(10.0f);

		SmallCloudActor_[1] = GetLevel()->CreateActor<SmallCloud>();
		SmallCloudActor_[1]->SetPosition({ 10.0f,470.0f });
		SmallCloudActor_[1]->SetSpeed(290.0f);

		SmallCloudActor_[2] = GetLevel()->CreateActor<SmallCloud>();
		SmallCloudActor_[2]->SetPosition({ 1740.0f,500.0f });
		SmallCloudActor_[2]->SetSpeed(500.0f);

		SmallCloudActor_[3] = GetLevel()->CreateActor<SmallCloud>();
		SmallCloudActor_[3]->SetPosition({ 1110.0f,580.0f });
		SmallCloudActor_[3]->SetSpeed(150.0f);

		SmallCloudActor_[4] = GetLevel()->CreateActor<SmallCloud>();
		SmallCloudActor_[4]->SetPosition({ 760.0f,530.0f });
		SmallCloudActor_[4]->SetSpeed(200.0f);
	}

	// 물 이미지
	WaterActor_ = GetLevel()->CreateActor<Water>();
	WaterActor_->SetPosition({ static_cast<float>( SCALE_CAMERA_MAPMOOKS_X) / 2, static_cast<float>(SCALE_CAMERA_MAPMOOKS_Y) - 50});


	// 플레이어 포지션 설정

	ResponPosition_[0] = { 244, 1164 };
	ResponPosition_[1] = { 250, 1050 };
	ResponPosition_[2] = { 300, 1025 };
	ResponPosition_[3] = { 330, 1000 };
	ResponPosition_[4] = { 390, 960 };
	ResponPosition_[5] = { 430, 950 };
	ResponPosition_[6] = { 470, 930 };
	ResponPosition_[7] = { 520, 910 };
	ResponPosition_[8] = { 585, 930 };
	ResponPosition_[9] = { 560, 1050 };
	ResponPosition_[10] = { 620, 1060 };
	ResponPosition_[11] = { 670, 960 };
	ResponPosition_[12] = { 720, 930 };
	ResponPosition_[13] = { 785, 903 };
	ResponPosition_[14] = { 857, 970 };
	ResponPosition_[15] = { 940, 940 };
	ResponPosition_[16] = { 1000, 990 };
	ResponPosition_[17] = { 1030, 1130 };
	ResponPosition_[18] = { 1070, 1060 };
	ResponPosition_[19] = { 1160, 910 };
	ResponPosition_[20] = { 1200, 900 };
	ResponPosition_[21] = { 1230, 900 };
	ResponPosition_[22] = { 1260, 900 };
	ResponPosition_[23] = { 1300, 890 };
	ResponPosition_[24] = { 1330, 885 };
	ResponPosition_[25] = { 1380, 885 };
	ResponPosition_[26] = { 1145, 960 };
	ResponPosition_[27] = { 1490, 1030 };
	ResponPosition_[28] = { 1530, 980 };
	ResponPosition_[29] = { 1580, 980 };
	ResponPosition_[30] = { 1640, 980 };
	ResponPosition_[31] = { 1670, 980 };
	ResponPosition_[32] = { 1700, 970 };
	ResponPosition_[33] = { 1730, 1040 };
	ResponPosition_[34] = { 655, 1240 };
	ResponPosition_[35] = { 700, 950 };
	ResponPosition_[36] = { 1050, 1060 };
	ResponPosition_[37] = { 1010, 1100 };
	ResponPosition_[38] = { 360, 970 };
	ResponPosition_[39] = { 1280, 900 };



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