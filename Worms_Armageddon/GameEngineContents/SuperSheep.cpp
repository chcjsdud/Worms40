#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PixelCollision.h"

SuperSheep::SuperSheep() 
	: IsSuper_(false)
	, ModeCnt_(0)
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

			WeaponRender_->ChangeAnimation(ANIM_NAME_SUPERSHEEP_90);
			IsSuper_ = true;
		}

		ThrowStart(0); // ����ü�� ������
		AnimalMove(); // ���� �����̴ٰ�
	}
	else // ���۾� ���
	{
		IsBounce_ = false;

		float Speed = 3.0f;
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
		{
			SetMove(float4::LEFT * Speed);
		}
		else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{
			SetMove(float4::RIGHT * Speed);
		}

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

void SuperSheep::SuperFly()
{

}