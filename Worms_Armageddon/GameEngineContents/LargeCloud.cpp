#include "LargeCloud.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

LargeCloud::LargeCloud() :
	CloudDir_(float4::ZERO),
	CloudSpeed_(0),
	WindDir_(0)
{
}

LargeCloud::~LargeCloud() 
{
}

void LargeCloud::Start()
{	
	CloudRenderer_ = CreateRenderer(10000);
	CloudRenderer_->CreateAnimation("cloudl.bmp", "CloudlAni", 0, 19, 0.05f, true,true);
	CloudRenderer_->ChangeAnimation("CloudlAni");

}

void LargeCloud::Update()
{
	//�ٶ��� ����� �ӵ��� �޾Ƽ� �̵���Ų��.
	if (WindDir_ == (int)WindType::Left)
	{
		CloudDir_ = float4::LEFT* GameEngineTime::GetDeltaTime() * CloudSpeed_;
	}
	else if (WindDir_ == (int)WindType::Right)
	{
		CloudDir_=float4::RIGHT *GameEngineTime::GetDeltaTime() * CloudSpeed_;
	}

	SetMove(CloudDir_);


	//ȭ��Ѿ�� �ݴ��� ����ġ
	if (-70.0f >= GetPosition().x)
	{
		SetPosition({ 1350.0f,GetPosition().y });
	}
	else if (1350 <= GetPosition().x)
	{
		SetPosition({ -70.0f,GetPosition().y });
	}
}

void LargeCloud::Render()
{
}
