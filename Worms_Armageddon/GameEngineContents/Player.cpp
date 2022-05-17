#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

Player::Player()
	: Speed_(1.0f)
	, MoveDir_(float4::ZERO)
	, PlayerRenderer_(nullptr)
{
}

Player::~Player()
{
}

void Player::Start()
{
	this->SetPosition({ 300, 300 });
	PlayerAnimationInit();
	PlayerKeyInit();
}

void Player::Update()
{
	UpdateCamera();
}

void Player::PlayerAnimationInit()
{
	PlayerRenderer_ = CreateRenderer(IMG_PLAYER_IDLE_RIGHT);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_RIGHT, ANIM_NAME_PLAYER_IDLE_RIGHT, 0, 0, 0.1f, false);

	PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_IDLE_RIGHT);
}

void Player::PlayerKeyInit()
{
	// 키설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		// 이동
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, VK_RIGHT);

		// 엔터
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_JUMP, VK_RETURN);
		// 백스페이스
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_BACKFLIP, VK_BACK);

		// 각도조절
		GameEngineInput::GetInst()->CreateKey(KEY_ANGLE_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(KEY_ANGLE_DOWN, VK_DOWN);
	}
}


// 눌리게 된 키가 있을경우 True
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_RIGHT)
		)
	{
		return false;
	}

	return true;
}

// 눌리고 있는 키가 있을경우 True
bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT)
		)
	{
		return false;
	}

	return true;
}

// 눌리지 않게 된 키가 있을경우 True
bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(KEY_MOVE_RIGHT)
		)
	{
		return false;
	}

	return true;
}

void Player::UpdateCamera()
{
	float CurrentLevelH = 0.0f;
	float CurrentLevelW = 0.0f;

	if (GetCurrentLevel() == IMG_MAPBOOKS)
	{
		CurrentLevelH = SCALE_MAPBOOKS_X;
		CurrentLevelW = SCALE_MAPBOOKS_Y;
	}

	// TODO::마우스 이동에 따라서 카메라 위치를 변경하거나
	// TODO::플레이어의 위치에 맞춰서 카메라가 따라다니거나의 2가지 모드
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	// 카메라가 맵 범위를 벗어났을경우 재위치
	if (CameraPos_.x <= 0)
	{
		CameraPos_.x = 0;
	}
	if (CameraPos_.x >= CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix())
	{
		CameraPos_.x = CurrentLevelW - GameEngineWindow::GetInst().GetScale().ix();
	}
	if (CameraPos_.y <= 0)
	{
		CameraPos_.y = 0;
	}
	if (CameraPos_.y >= CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy())
	{
		CameraPos_.y = CurrentLevelH - GameEngineWindow::GetInst().GetScale().iy();
	}

	// 카메라 위치 갱신
	GetLevel()->SetCameraPos(CameraPos_);
}



// 상태 변경
void Player::StateChange(PlayerState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			break;
		case PlayerState::Move:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}


// 상태 업데이트
void Player::StateUpdate()
{
	switch (CurrentState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}