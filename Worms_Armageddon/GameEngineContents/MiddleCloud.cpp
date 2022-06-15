#include "MiddleCloud.h"
#include "Enums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

MiddleCloud::MiddleCloud() :
	CloudDir_(float4::ZERO),
	CloudSpeed_(0),
	WindDir_(0),
	MySpeed_(0),
	CloudRenderer_(nullptr)
{
}

MiddleCloud::~MiddleCloud()
{
}

void MiddleCloud::Start()
{
	CloudRenderer_ = CreateRenderer((int)RenderOrder::BackGround_3);
	CloudRenderer_->CreateAnimation("cloudm.bmp", "CloudmAni", 0, 19, 0.05f, true, true);
	CloudRenderer_->ChangeAnimation("CloudmAni");

}

void MiddleCloud::Update()
{
	//�ٶ��� ����� �ӵ��� �޾Ƽ� �̵���Ų��.
	if (WindDir_ == (int)WindType::Left)
	{
		CloudDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * CloudSpeed_;
	}
	else if (WindDir_ == (int)WindType::Right)
	{
		CloudDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * CloudSpeed_;
	}

	SetMove(CloudDir_);


	//ȭ��Ѿ�� �ݴ��� ����ġ
	if (-70.0f >= GetPosition().x)
	{
		SetPosition({ 2100.0f,GetPosition().y });
	}
	else if (2100 <= GetPosition().x)
	{
		SetPosition({ -70.0f,GetPosition().y });
	}
}

void MiddleCloud::Render()
{
}
