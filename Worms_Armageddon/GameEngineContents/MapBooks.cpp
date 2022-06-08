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
	
	//������ ī�޶����� ���� �ʰ�
	BackGround_->CameraEffectOff();

	// �浹���� ������?
	ColMapRenderer_= CreateRendererToScale(IMG_MAPBOOKS_GROUND, { 5000.0f * 0.4f, 3200.0 * 0.4f }, (int)RenderOrder::BackGround_2);
	ColMapHalf = ColMapRenderer_->GetScale().Half();
	ColMapRenderer_->SetPivot(ColMapHalf);

	// �� ������
	Ground_ = CreateRendererToScale(IMG_MAPBOOKS, { SCALE_MAPBOOKS_X, SCALE_MAPBOOKS_Y }, (int)RenderOrder::BackGround_2);
	GroundHalf = Ground_->GetScale().Half();
	Ground_->SetPivot(GroundHalf);

	ColMap_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);



	// ��� �̹���
	LargeCloudActor_ = GetLevel()->CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200.0f,200.0f });
	SmallCloudActor_ = GetLevel()->CreateActor<SmallCloud>();
	SmallCloudActor_->SetPosition({ 250.0f,200.0f });

	// �� �̹���
	WaterActor_ = GetLevel()->CreateActor<Water>();
	WaterActor_->SetPosition({ SCALE_CAMERA_MAPMOOKS_X / 2, SCALE_CAMERA_MAPMOOKS_Y - 50});


	// �÷��̾� ������ ����

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