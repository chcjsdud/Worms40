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
	// TODO::동작이 끝날경우에 Idle로 전환
	StateChange(PlayerState::Idle);
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

void Player::ActionStart()
{

}