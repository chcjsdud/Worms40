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
	// ������
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