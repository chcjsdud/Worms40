#include "LobbyShootingStar.h"
#include "Enums.h"

#include <GameEngineBase/GameEngineTime.h>

LobbyShootingStar::LobbyShootingStar()
	:
	CreateTimer_(0.f),

	RandomCreateTimer_(),
	RandomPosX_(),
	RandomPosY_(),

	ShootingParticle_(nullptr),
	CreateStarState_(CreateStar::SetTimer)
{
}

LobbyShootingStar::~LobbyShootingStar()
{
}

void LobbyShootingStar::Start()
{
}

void LobbyShootingStar::Update()
{

	switch (CreateStarState_)
	{
	case CreateStar::SetTimer:

		CreateTimer_ = RandomCreateTimer_.RandomFloat(0.2f, 0.4f);
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
		ShootingParticle_->SetPosition({ RandomPosX_.RandomFloat(-1280.f, 1280.f), RandomPosY_.RandomFloat(-600.f, 0) });
		ShootingParticle_->SetDirection(float4::RIGHT);
		CreateStarState_ = CreateStar::SetTimer;

		break;
	default:
		break;
	}

}
