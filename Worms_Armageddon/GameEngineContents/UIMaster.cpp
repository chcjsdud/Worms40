#include "UIMaster.h"
#include <GameEngineBase/GameEngineTime.h>

UIMaster::UIMaster()
	: State_(STATE::IDLE)
	, StartPos_(float4::ZERO)
	, DestPos_(float4::ZERO)
{
}

UIMaster::~UIMaster() 
{
}


void UIMaster::Start()
{
	ChangeState(STATE::IDLE);
}

void UIMaster::Update()
{
}

void UIMaster::UpdateState()
{
	switch (State_)
	{
	case UIMaster::STATE::IDLE:
		IdleUpdate();
		break;
	case UIMaster::STATE::MOVING:
		MovingUpdate();
		break;
	default:
		break;
	}
}

void UIMaster::ChangeState(STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case UIMaster::STATE::IDLE:
			break;
		case UIMaster::STATE::MOVING:
			MovingStart();
			break;
		default:
			break;
		}
	}

	State_ = _State;
}

void UIMaster::MovingStart()
{
	LerpDeltaTime_ = 0.0f;
}

void UIMaster::IdleUpdate()
{

}

void UIMaster::MovingUpdate()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime();
	LerpDeltaTime_ += DeltaTime_;

	CurPos_ = GetPosition();

	float4 Pos = float4::LerpLimit(CurPos_, DestPos_, LerpDeltaTime_);
	SetPosition(Pos);

	if (CurPos_.x > DestPos_.x - 1.0f && CurPos_.x < DestPos_.x + 1.0f &&
		CurPos_.y > DestPos_.y - 1.0f && CurPos_.y < DestPos_.y + 1.0f)
	{
		SetPosition(DestPos_);
		ChangeState(STATE::IDLE);
	}
}

void UIMaster::MoveSetting(float4 _StartPos, float4 _DestPos, float _Speed)
{
	StartPos_ = _StartPos;
	DestPos_ = _DestPos;
	Speed_ = _Speed;

	LerpDeltaTime_ = 0.0f;
}

void UIMaster::Move()
{
	ChangeState(STATE::MOVING);
}