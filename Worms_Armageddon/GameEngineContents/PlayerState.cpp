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
	Weapon_->SetWeaponDir(MoveDir_);
	Weapon_->SetColMapImage(ColMapImage_);
}