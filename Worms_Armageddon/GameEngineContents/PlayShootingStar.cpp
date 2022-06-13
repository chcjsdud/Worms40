#include "PlayShootingStar.h"
#include "Enums.h"

#include <GameEngineBase/GameEngineTime.h>

PlayShootingStar::PlayShootingStar()
	:
	CreateTimer_(0.f),

	RandomCreateTimer_(),
	RandomPosX_(),
	RandomPosY_(),

	ShootingStarParticle_(nullptr),
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

		CreateTimer_ = RandomCreateTimer_.RandomFloat(0.05f, 0.07f);
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

		ShootingStarParticle_ = (GetLevel()->CreateActor<ShootingStarParticle>(static_cast<int>(RenderOrder::LobbyStar)));
		ShootingStarParticle_->SetPosition({ RandomPosX_.RandomFloat(-3840.f, 3840.f), RandomPosY_.RandomFloat(-1392.f, 0) });
		ShootingStarParticle_->SetDeleteY(3840.f);
		ShootingStarParticle_->SetSpeed(300.f);

		CreateStarState_ = CreateStar::SetTimer;

		break;
	default:
		break;
	}

}
