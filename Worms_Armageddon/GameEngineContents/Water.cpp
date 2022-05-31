#include "Water.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>


Water::Water() 
{
}

Water::~Water() 
{
}

void Water::Start()
{
	WaterRenderer4_ = CreateRenderer();
	WaterRenderer4_->CreateAnimation("Water_sprite.bmp", "WaterAni", 0, 9, 0.05f, true);
	WaterRenderer4_->ChangeAnimation("WaterAni");
	WaterRenderer4_->SetPivot({ 90.0f,-75.0f });
	WaterRenderer4_->SetOrder((int)RenderOrder::BackGround_1);

	WaterRenderer3_ = CreateRenderer();
	WaterRenderer3_->CreateAnimation("Water_sprite.bmp", "WaterAni", 0, 9, 0.06f, true);
	WaterRenderer3_->ChangeAnimation("WaterAni");
	WaterRenderer3_->SetPivot({ WaterRenderer3_->GetPivot().x,-50.0f});
	WaterRenderer3_->SetOrder((int)RenderOrder::BackGround_1);

	WaterRenderer2_ = CreateRenderer();
	WaterRenderer2_->CreateAnimation("Water_sprite.bmp", "WaterAni", 0, 9, 0.05f, true);
	WaterRenderer2_->ChangeAnimation("WaterAni");
	WaterRenderer2_->SetPivot({ 30.0f,-25.0f });
	WaterRenderer2_->SetOrder((int)RenderOrder::BackGround_3);

	WaterRenderer1_ = CreateRenderer();
	WaterRenderer1_->CreateAnimation("Water_sprite.bmp", "WaterAni", 0, 9, 0.05f, true);
	WaterRenderer1_->ChangeAnimation("WaterAni");
	WaterRenderer1_->SetOrder((int)RenderOrder::BackGround_3);


	// TODO::UnderWater ¸¸µé±â
}

void Water::Update()
{
}

void Water::Render()
{
}
