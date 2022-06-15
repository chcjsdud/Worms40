#include "ShootingParticle.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <math.h>


float4 ShootingParticle::MoveDirection_ = float4::RIGHT;

ShootingParticle::ShootingParticle()
	:
	StarRenderer_(nullptr),
	StarUpdate_(true),
	LimitY_(GameEngineWindow::GetInst().GetScale().y),
	Speed_(150.f)
{
	GameEngineRandom Random_;
	CosAngle_ = Random_.RandomFloat(0.0f, 1.0f);
}

ShootingParticle::~ShootingParticle()
{
}

void ShootingParticle::Start()
{
	StarRenderer_ = CreateRenderer("stars.bmp", static_cast<int>(RenderOrder::PlayStar));
	StarRenderer_-> CreateAnimation("stars.bmp", "STAR_ANIMATION", 0, 128, 0.02f, true);
	StarRenderer_->CreateAnimation("ScatterLeaf.bmp", "LEAF_ANIMATION", 0, 12, 0.1f, true);

	StarRenderer_->ChangeAnimation("STAR_ANIMATION");

	StarRenderer_->SetScale({35, 35});
}

void ShootingParticle::Update()
{
	StarUpdate();
	LeafUpdate();
}

void ShootingParticle::SetDirection(float4 _Direction)
{
	MoveDirection_.x = _Direction.x;
}

void ShootingParticle::SetDeleteY(float _PosY)
{
	LimitY_ = _PosY;
}

void ShootingParticle::SetSpeed(float _SetSpeed)
{
	Speed_ = _SetSpeed;
}

void ShootingParticle::SetStarAnimation()
{
	StarRenderer_->ChangeAnimation("STAR_ANIMATION");
}

void ShootingParticle::SetLeafAnimation()
{
	StarRenderer_->ChangeAnimation("LEAF_ANIMATION");

}

void ShootingParticle::SetLeafCurve()
{
	StarUpdate_ = false;
}

void ShootingParticle::StarUpdate()
{
	if (StarUpdate_ == true)
	{
		CosAngle_ += (0.005f);

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		SetMove({ MoveDirection_.x * GameEngineTime::GetDeltaTime() * Speed_, sinf(CosAngle_) / 3 });

		if (this->GetPosition().y > LimitY_)
		{
			this->Death();
		}
	}
}

void ShootingParticle::LeafUpdate()
{
	if (StarUpdate_ == false)
	{
		CosAngle_ += (0.005f);

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 40.f);
		SetMove({ MoveDirection_.x * GameEngineTime::GetDeltaTime() * Speed_, sinf(CosAngle_)  });

		if (this->GetPosition().y > LimitY_)
		{
			this->Death();
		}
	}
}
