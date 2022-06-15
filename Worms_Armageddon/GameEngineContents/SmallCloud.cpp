#include "SmallCloud.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


SmallCloud::SmallCloud() 
{
}

SmallCloud::~SmallCloud() 
{
}

void SmallCloud::Start()
{
	CloudRenderer_ = CreateRenderer((int)RenderOrder::BackGround_3);
	CloudRenderer_->CreateAnimation("clouds.bmp", "CloudsAni", 0, 19,0.05f, true, true);
	CloudRenderer_->ChangeAnimation("CloudsAni");
}

void SmallCloud::Update()
{
	//�ٶ��� ����� �ӵ��� �޾Ƽ� �̵���Ų��.
	if (WindDir_ == (int)WindType::Left)
	{
		CloudDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * CloudSpeed_*2.0f;
	}
	else if (WindDir_ == (int)WindType::Right)
	{
		CloudDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * CloudSpeed_*2.0f;
	}

	SetMove(CloudDir_);


	//ȭ��Ѿ�� �ݴ��� ����ġ
	if (-30.0f >= GetPosition().x)
	{
		SetPosition({ 2100.0f,GetPosition().y });
	}
	else if (2100 <= GetPosition().x)
	{
		SetPosition({ -30.0f,GetPosition().y });
	}
}

void SmallCloud::Render()
{
}
