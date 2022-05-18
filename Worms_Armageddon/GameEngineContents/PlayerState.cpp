#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

void Player::IdleUpdate()
{
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

		ColCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		//PlayerAnimationChange(ANIM_WALK_LEFT);

		ColCheck(float4::LEFT);
	}
}

void Player::ActionUpdate()
{
	// TODO::������ ������쿡 Idle�� ��ȯ
	StateChange(PlayerState::Idle);
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

}