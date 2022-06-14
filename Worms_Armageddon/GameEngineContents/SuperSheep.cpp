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
	
	for (size_t i = 0; i < 32; i++)
	{
		int AnimIndex = i * 2;
		WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, "spsheepAngle-" + std::to_string(i), AnimIndex, AnimIndex + 1, AnimSpeed);
	}

	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
}

void SuperSheep::Update()
{

}

bool SuperSheep::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	if (false == IsSuper_) // �� ���
	{
		IsBounce_ = true;

		if (1 == ShotDir_.x) // ���� �ٶ󺸴� ������ ������
		{
			WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
		}

		// ��� ��ȯ
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			if (1 == ModeCnt_)
			{
				Explosion();
			}

			WeaponRender_->ChangeAnimation("spsheepAngle-8");
			IsSuper_ = true;
		}

		ThrowStart(0); // ����ü�� ������
		AnimalMove(); // ���� �����̴ٰ�
	}
	else // ���۾� ���
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

			CycleFlyRender(0);
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

			CycleFlyRender(1);
		}

		SetMove(SheepFlyDir_ * Speed);

		// ��� ��ȯ
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
			IsSuper_ = false;
			++ModeCnt_;
		}

		BulletColEvent();
	}

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}

void SuperSheep::CycleFlyRender(int _CycleDir)
{
	if (0 == _CycleDir)
	{
		int AnimAngle = (int)SpDegree_ % 360;
		AnimAngle = AnimAngle / 11.25f;
		WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(AnimAngle));
	}
	else
	{
		int AnimAngle = (int)SpDegree_ % 360;
		AnimAngle = AnimAngle / 11.25f;
		AnimAngle = 31 - AnimAngle;
		WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(AnimAngle));
	}
}