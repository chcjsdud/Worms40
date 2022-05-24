#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include "Baz.h"

void Player::IdleUpdate()
{
	// �׼��� �̵����� �켱������ ����.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	// �̵�Ű�� ������ �̵�
	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}
	//����Ű ������ ����
	if (true == IsJumpKeyDown())
	{
		StateChange(PlayerState::Jump);
		return;
	}

}

void Player::MoveUpdate()
{
	// �׼��� �̵����� �켱������ ����.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	// Ű�� ����������� Idle���·� ��ȯ
	if (true == IsMoveKeyUp() && false == IsMoveKeyPress())
	{
		StateChange(PlayerState::Idle);
		return;
	}


	// �̵� ���¿��� ����
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
		// TODO::������ ������쿡 Idle�� ��ȯ
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
	// �ƹ��͵� ������ ������
	// TODO::���� ��� �ִ� ������ ������ ���� �̹����� ����?
	PlayerAnimationChange(StateName_);
}

void Player::MoveStart()
{
	// �̵��� ������
}

void Player::ActionStart()
{
	// ���� ���� ����
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