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
			break;
		default:
			break;
		}
	}

	State_ = _State;
}

void UIMaster::IdleUpdate()
{

}

void UIMaster::MovingUpdate()
{
	DeltaTime_ = GameEngineTime::GetDeltaTime();
	CurPos_ = GetPosition();

	MoveDir_ = DestPos_ - CurPos_;
	MoveDir_.Normal2D();
	SetMove(MoveDir_ * DeltaTime_ * Speed_);

	// 다 움직이면 멈추기
	if (CurPos_.x > DestPos_.x - 20.0f && CurPos_.x < DestPos_.x + 20.0f &&
		CurPos_.y > DestPos_.y - 20.0f && CurPos_.y < DestPos_.y + 20.0f)
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
}

void UIMaster::Move()
{
	ChangeState(STATE::MOVING);
}