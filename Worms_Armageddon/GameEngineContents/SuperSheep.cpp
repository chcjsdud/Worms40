#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PixelCollision.h"
#include "TimerBox.h"
#include "Skidmark.h"

SuperSheep::SuperSheep() 
	: IsSuper_(false)
	, ModeCnt_(0)
	, SpDegree_(270.f)
	, SheepFlyDir_(float4::UP)
	, SpSoundOn_(false)
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
	

	//������ : ���� ���� �۾�. siez_t ���� int�� ����
	for (int i = 0; i < 32; i++)
	{
		int AnimIndex = i * 2;
		WeaponRender_->CreateAnimation(IMG_SUPERSHEEP_FLY, ANIM_NAME_SPSHEEP_FLY + std::to_string(i), AnimIndex, AnimIndex + 1, AnimSpeed);
	}

	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);

	SelfDestructSec_ = 10.f;
}

void SuperSheep::Update()
{

}

bool SuperSheep::WeaponUpdate()
{
	if (true == WeaponMaster::IsBulletOutofBound()) // �ٴٿ� ������
	{
		if (nullptr != TimerBox_)
		{
			GetTimerBox()->DeleteGrenadeBox();
		}
		SoundPlayer_SpSheep.Stop();
		Off();
		return false;
	}

	if (SelfDestructSec_ - 5.f < GetAccTime() && false == IsTimerCreate_) // Ÿ�̸� �ڽ� ����
	{
		CreateTimerBox(MyTeamColor_);
		IsTimerCreate_ = true;
	}

	if (SelfDestructSec_ < GetAccTime()) // ����
	{
		GetTimerBox()->DeleteGrenadeBox();
		SoundPlayer_SpSheep.Stop();
		Explosion();
		return false;
	}

	//Ÿ�̸� �ڽ� ��ġ
	if (GetTimerBox() != nullptr)
	{
		GetTimerBox()->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
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
				if (nullptr != TimerBox_)
				{
					GetTimerBox()->DeleteGrenadeBox();
				}
				SoundPlayer_SpSheep.Stop();
				Explosion();
				return false;
			}

			SoundPlayer_SpSheep = GameEngineSound::SoundPlayControl("SUPERSHEEPRELEASE.wav");
			SoundPlayer_SpSheep.Volume(SND_VOL_BAZEXPLODE);

			WeaponRender_->ChangeAnimation("spsheepAngle-8");
			IsSuper_ = true;
		}

		ThrowStart(0); // ����ü�� ������
		AnimalMove(); // ���� �����̴ٰ�
	}
	else // ���۾� ���
	{
		if (false == SpSoundOn_)
		{
			SoundPlayer_SpSheep = GameEngineSound::SoundPlayControl("SUPERSHEEPWHOOSH.wav",10);
			SoundPlayer_SpSheep.Volume(SND_VOL_BAZEXPLODE);
			SpSoundOn_ = true;
		}
		

		IsBounce_ = false;
		float Speed = 5.0f;

		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
		{ // - Angle_
			CycleFly(0);
		}
		else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{ // + Angle_
			CycleFly(1);
		}

		//EffectManager* Effect = GetLevel()->CreateActor<Skidmark>();
		//Effect->SetPosition(GetPosition());

		SetMove(SheepFlyDir_ * Speed);

		// ��� ��ȯ
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			SoundPlayer_SpSheep.Stop();
			WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
			IsSuper_ = false;
			++ModeCnt_;
		}
		
		bool BulletCol = BulletColEvent();
		if (false == BulletCol)
		{
			SoundPlayer_SpSheep.Stop();
			if (nullptr != TimerBox_)
			{
				GetTimerBox()->DeleteGrenadeBox();
			}
		}
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


void SuperSheep::CycleFly(int _CycleDir)
{
	if (360.0f < SpDegree_)
	{
		SpDegree_ = 0.0f;
	}
	else if (0 > SpDegree_)
	{
		SpDegree_ = 360.0f;
	}

	// ������ ���� ���
	int AnimAngle = (int)SpDegree_ % 360;
	AnimAngle = static_cast<int>(AnimAngle / 11.25f);
	AnimAngle = 31 - AnimAngle;

	if (0 == _CycleDir)
	{
		SpDegree_ -= GameEngineTime::GetDeltaTime() * 270.0f;
		SheepFlyDir_ = float4::DegreeToDirectionFloat4(SpDegree_);

		WeaponRender_->ChangeAnimation(ANIM_NAME_SPSHEEP_FLY + std::to_string(AnimAngle));
	}
	else
	{
		SpDegree_ += GameEngineTime::GetDeltaTime() * 270.0f;
		SheepFlyDir_ = float4::DegreeToDirectionFloat4(SpDegree_);

		WeaponRender_->ChangeAnimation(ANIM_NAME_SPSHEEP_FLY + std::to_string(AnimAngle));
	}
}