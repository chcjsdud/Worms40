#include "PlayShootingStar.h"
#include "Enums.h"

#include <GameEngineBase/GameEngineTime.h>

PlayShootingStar::PlayShootingStar()
	:
	CreateTimer_(0.f),

	RandomCreateTimer_(),
	RandomPosX_(),
	RandomPosY_(),

	Dir_(false),

	ShootingParticle_(nullptr),
	CreateStarState_(CreateStar::SetTimer)
{
}

PlayShootingStar::~PlayShootingStar()
{
}

void PlayShootingStar::Start()
{
}

void PlayShootingStar::Update()
{



	switch (CreateStarState_)
	{
	case CreateStar::SetTimer:

		CreateTimer_ = RandomCreateTimer_.RandomFloat(0.09f, 0.13f);
		CreateStarState_ = CreateStar::AddTime;

		break;
	case CreateStar::AddTime:

		CreateTimer_ -= GameEngineTime::GetInst()->GetDeltaTime();

		if (CreateTimer_ <= 0)
		{
			CreateStarState_ = CreateStar::Create;
		}

		break;
	case CreateStar::Create:

		ShootingParticle_ = (GetLevel()->CreateActor<ShootingParticle>(static_cast<int>(RenderOrder::LobbyStar)));
		ShootingParticle_->SetPosition({ RandomPosX_.RandomFloat(-3840.f, 3840.f), RandomPosY_.RandomFloat(-100.f, 300.f) });
		ShootingParticle_->SetDeleteY(3840.f);
		ShootingParticle_->SetLeafAnimation();
		ShootingParticle_->SetLeafCurve();

		if (Dir_ == true)
		{
			ShootingParticle_->SetDirection(float4::LEFT);

		}
		else
		{
			ShootingParticle_->SetDirection(float4::RIGHT);

		}

		CreateStarState_ = CreateStar::SetTimer;

		break;
	default:
		break;
	}

}

void PlayShootingStar::SetLeftDir()
{
	Dir_ = true;
}

void PlayShootingStar::SetRightDir()
{
	Dir_ = false;
}
