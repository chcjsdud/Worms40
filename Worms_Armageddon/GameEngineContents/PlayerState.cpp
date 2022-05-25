#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>

#pragma region Weapon
#include "Baz.h"
#include "Grenade.h"
#pragma endregion


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

	if (GameEngineInput::GetInst()->IsPress(KEY_WEAPON_BAZ))
	{
		WeaponState_ = WeaponState::Baz;
	}
	if (GameEngineInput::GetInst()->IsPress(KEY_WEAPON_GRENADE))
	{
		WeaponState_ = WeaponState::Grenade;
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
	switch (WeaponState_)
	{
	case WeaponState::Baz:
		Weapon_ = GetLevel()->CreateActor<Baz>();
		break;
	case WeaponState::Homing:
		break;
	case WeaponState::Mortar:
		break;
	case WeaponState::Grenade:
		Weapon_ = GetLevel()->CreateActor<Grenade>();
		break;
	case WeaponState::Axe:
		break;
	case WeaponState::Uzi:
		break;
	case WeaponState::FirePunch:
		break;
	case WeaponState::Sheep:
		break;
	case WeaponState::AirStrike:
		break;
	case WeaponState::BlowTorch:
		break;
	case WeaponState::Drill:
		break;
	case WeaponState::Grider:
		break;
	default:
		// �⺻�� ����ī
		Weapon_ = GetLevel()->CreateActor<Baz>();
		break;
	}

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