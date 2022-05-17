#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

void Player::IdleUpdate()
{
	// 이동키가 눌리면 이동
	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}
}

void Player::MoveUpdate()
{
	// 움직임
}


void Player::IdleStart()
{
	// 아무것도 안함을 시작함
	// TODO::현재 들고 있는 무기의 종류에 따라서 이미지를 변경?
	// ChangeAnimation
}

void Player::MoveStart()
{
	// 이동을 시작함
}