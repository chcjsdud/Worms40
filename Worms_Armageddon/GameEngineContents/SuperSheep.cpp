#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PixelCollision.h"

SuperSheep::SuperSheep() 
	: IsSuper_(false)
	, ModeCnt_(0)
	, SpDegree_(90.f)
	, SheepFlyDir_(float4::UP)
{
}

SuperSheep::~SuperSheep() 
{
}

void SuperSheep::Start()
{
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_LEFT, ANIM_NAME_SHEEP_LEFT, 0, 7, 0.04f);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_RIGHT, ANIM_NAME_SHEEP_RIGHT, 0, 7, 0.04f);

	for (size_t i = 0; i < 360; ++i)
	{
		int AnimAngle;
	}

	float AnimSpeed = 0.08f;
	int AnimIndex = 0;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_90, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_80, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_70, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_60, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_50, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_30, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_20, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_10, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_0, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_350, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_340, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_330, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_320, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_310, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_290, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_280, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_270, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_260, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_250, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_240, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_230, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_220, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_200, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_190, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_180, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_170, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_160, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_150, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_140, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_130, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_110, AnimIndex, AnimIndex + 1, AnimSpeed);
	AnimIndex += 2;
	WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SUPERSHEEP_100, AnimIndex, AnimIndex + 1, AnimSpeed);
	
	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);

	// 0 <= angle <= 359
	// static_cast<int>(angle/10);
	//WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(10));
}

void SuperSheep::Update()
{

}

void SuperSheep::Render()
{
	if (IsSuper_)
	{
		int AnimAngle = (int)SpDegree_ % 360;

		AnimAngle = AnimAngle / 11.25f;
		
		WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(AnimAngle));
	}
}

bool SuperSheep::WeaponUpdate()
{
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	if (false == IsSuper_) // 양 모드
	{
		IsBounce_ = true;

		if (1 == ShotDir_.x) // 양이 바라보는 방향이 오른쪽
		{
			WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
		}

		// 모드 전환
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			if (1 == ModeCnt_)
			{
				Explosion();
			}

			WeaponRender_->ChangeAnimation(ANIM_NAME_SUPERSHEEP_90);
			IsSuper_ = true;
		}

		ThrowStart(0); // 투사체를 던지고
		AnimalMove(); // 양이 움직이다가
	}
	else // 슈퍼양 모드
	{
		IsBounce_ = false;
		float Speed = 3.0f;

		if (false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT) &&
			false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{
			//IsAngleInit_ = false;
		}

		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
		{ // - Angle_

			SpDegree_ += SpDegree_ * GameEngineTime::GetDeltaTime() * 1.f;
			float CalDegree = -1.f * SpDegree_;
			SheepFlyDir_ = float4::DegreeToDirectionFloat4(CalDegree);

			if (720.f < SpDegree_)
			{
				SpDegree_ = 360.f;
			}
		}
		else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{ // + Angle_


			SpDegree_ += SpDegree_ * GameEngineTime::GetDeltaTime() * 1.f;
			float CalDegree = 1.f * SpDegree_;
			SheepFlyDir_ = float4::DegreeToDirectionFloat4(CalDegree);

			if (720.f < SpDegree_)
			{
				SpDegree_ = 360.f;
			}
		}

		SetMove(SheepFlyDir_ * Speed);

		// 모드 전환
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
			IsSuper_ = false;
			++ModeCnt_;
		}

		BulletColEvent();
	}

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}

void SuperSheep::CycleFly()
{
	
}