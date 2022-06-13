#include "ShootingStarParticle.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <math.h>

ShootingStarParticle::ShootingStarParticle()
	:
	StarRenderer_(nullptr)
{
	GameEngineRandom Random_;
	CosAngle_ = Random_.RandomFloat(0.0f, 1.0f);
}

ShootingStarParticle::~ShootingStarParticle()
{
}

void ShootingStarParticle::Start()
{
	StarRenderer_ = CreateRenderer("stars.bmp", static_cast<int>(RenderOrder::LobbyStar));
	StarRenderer_-> CreateAnimation("stars.bmp", "STAE_ANIMATION", 0, 128, 0.02f, true);
	StarRenderer_->ChangeAnimation("STAE_ANIMATION");

	StarRenderer_->SetScale({35, 35});
}

void ShootingStarParticle::Update()
{
	CosAngle_ += 0.005f;

	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 150.f);
	SetMove({float4::RIGHT.x * GameEngineTime::GetDeltaTime() * 150.f, sinf(CosAngle_) / 3 });

	if (this->GetPosition().y > GameEngineWindow::GetInst().GetScale().y)
	{
		this->Death();
	}
}
