#include "ShootingStarParticle.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <math.h>

ShootingStarParticle::ShootingStarParticle()
	:
	StarRenderer_(nullptr),
	LimitY_(GameEngineWindow::GetInst().GetScale().y),
	MoveDirection_(float4::RIGHT),
	Speed_(150.f)
{
	GameEngineRandom Random_;
	CosAngle_ = Random_.RandomFloat(0.0f, 1.0f);
}

ShootingStarParticle::~ShootingStarParticle()
{
}

void ShootingStarParticle::Start()
{
	StarRenderer_ = CreateRenderer("stars.bmp", static_cast<int>(RenderOrder::PlayStar));
	StarRenderer_-> CreateAnimation("stars.bmp", "STAE_ANIMATION", 0, 128, 0.02f, true);
	StarRenderer_->ChangeAnimation("STAE_ANIMATION");

	StarRenderer_->SetScale({35, 35});
}

void ShootingStarParticle::Update()
{
	CosAngle_ += (0.005f * MoveDirection_.x);

	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	SetMove({float4::RIGHT.x * GameEngineTime::GetDeltaTime() * Speed_, sinf(CosAngle_) / 3 });

	if (this->GetPosition().y > LimitY_)
	{
		this->Death();
	}
}

void ShootingStarParticle::SetDirectionLeft(float4 _Direction)
{
	MoveDirection_.x = _Direction.x;
}

void ShootingStarParticle::SetDeleteY(float _PosY)
{
	LimitY_ = _PosY;
}

void ShootingStarParticle::SetSpeed(float _SetSpeed)
{
	Speed_ = _SetSpeed;
}
