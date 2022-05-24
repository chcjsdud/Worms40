#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include "Baz.h"

void Player::IdleUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	// 이동키가 눌리면 이동
	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}
	//점프키 눌리면 점프
	if (true == IsJumpKeyDown())
	{
		StateChange(PlayerState::Jump);
		return;
	}

}

void Player::MoveUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	// 키가 떨어졌을경우 Idle상태로 전환
	if (true == IsMoveKeyUp() && false == IsMoveKeyPress())
	{
		StateChange(PlayerState::Idle);
		return;
	}


	// 이동 상태에서 방향
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		StateName_ = ANIM_KEYWORD_PLAYER_WALK;
		MoveCheck(float4::RIGHT);
		
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		StateName_ = ANIM_KEYWORD_PLAYER_WALK;
		MoveCheck(float4::LEFT);

	}


	PlayerAnimationChange(StateName_);
}

void Player::ActionUpdate()
{
	if (false == Weapon_->WeaponUpdate())
	{
		// TODO::동작이 끝날경우에 Idle로 전환
		StateChange(PlayerState::Idle);
	}
}

void Player::JumpUpdate()
{
	JumpDelayTime_ -= GameEngineTime::GetDeltaTime();
	if (0 >= JumpDelayTime_)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_JUMP;
		PlayerAnimationChange(StateName_);

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;

		float4 DownPos = GetPosition() + float4{ 0.0f , PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);

		if (RGB(0, 0, 255) == Color)
		{
			MoveDir_ = float4::ZERO;
			StateChange(PlayerState::Idle);
		}
	}
}

void Player::IdleStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
	// 아무것도 안함을 시작함
	// TODO::현재 들고 있는 무기의 종류에 따라서 이미지를 변경?
	PlayerAnimationChange(StateName_);
}

void Player::MoveStart()
{
	// 이동을 시작함
}

void Player::ActionStart()
{
	// 무기 액터 생성
	Weapon_ = GetLevel()->CreateActor<Baz>();
	Weapon_->SetPosition(this->GetPosition());
	Weapon_->SetShotDir(MoveDir_);
}

void Player::JumpStart()
{
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 400.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);
}