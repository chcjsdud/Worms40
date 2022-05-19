#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
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
		//PlayerAnimationChange(ANIM_WALK_RIGHT);

		MoveCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		//PlayerAnimationChange(ANIM_WALK_LEFT);

		MoveCheck(float4::LEFT);
	}
}

void Player::ActionUpdate()
{
	if (false == Weapon_->WeaponUpdate())
	{
		// TODO::������ ������쿡 Idle�� ��ȯ
		StateChange(PlayerState::Idle);
	}
}


void Player::IdleStart()
{
	// �ƹ��͵� ������ ������
	// TODO::���� ��� �ִ� ������ ������ ���� �̹����� ����?
	// ChangeAnimation
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
}