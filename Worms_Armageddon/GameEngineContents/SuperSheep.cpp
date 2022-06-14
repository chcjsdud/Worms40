#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PixelCollision.h"
#include "TimerBox.h"
#include "Skidmark.h"

SuperSheep::SuperSheep() 
	: IsSuper_(false)
	, ModeCnt_(0)
	, SpDegree_(90.f)
	, SheepFlyDir_(float4::UP)
	, TimerBox_(nullptr)
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
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	if (20.0f < GetAccTime()) // 20초 후 폭발
	{
		Explosion();
		TimerBox_->DeleteGrenadeBox();
		return false;
	}

	//타이머 박스 위치
	if (TimerBox_ != nullptr)
	{
		TimerBox_->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
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
				return false;
			}

			WeaponRender_->ChangeAnimation("spsheepAngle-8");
			IsSuper_ = true;
		}

		ThrowStart(0); // 투사체를 던지고
		AnimalMove(); // 양이 움직이다가
	}
	else // 슈퍼양 모드
	{
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

		EffectManager* Effect = GetLevel()->CreateActor<Skidmark>();
		Effect->SetPosition(GetPosition());

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

void SuperSheep::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), 10);
}

void SuperSheep::CycleFly(int _CycleDir)
{
	if (720.f < SpDegree_)
	{
		SpDegree_ = 360.f;
	}

	SpDegree_ += SpDegree_ * GameEngineTime::GetDeltaTime() * 0.8f;

	if (0 == _CycleDir)
	{
		float CalDegree = -1.f * SpDegree_;
		SheepFlyDir_ = float4::DegreeToDirectionFloat4(CalDegree);

		int AnimAngle = (int)SpDegree_ % 360;
		AnimAngle = AnimAngle / 11.25f;
		WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(AnimAngle));
	}
	else
	{
		float CalDegree = 1.f * SpDegree_;
		SheepFlyDir_ = float4::DegreeToDirectionFloat4(CalDegree);

		int AnimAngle = (int)SpDegree_ % 360;
		AnimAngle = AnimAngle / 11.25f;
		AnimAngle = 31 - AnimAngle;
		WeaponRender_->ChangeAnimation("spsheepAngle-" + std::to_string(AnimAngle));
	}
}