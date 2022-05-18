#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

Player::Player()
	: Speed_(50.0f)
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
	StateUpdate();
}

void Player::Render()
{

}

void Player::PlayerAnimationInit()
{
	PlayerRenderer_ = CreateRenderer((int)RenderOrder::Player);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_RIGHT, ANIM_NAME_PLAYER_IDLE_RIGHT, 0, 5, 0.1f, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_LEFT, ANIM_NAME_PLAYER_IDLE_LEFT, 0, 5, 0.1f, true);

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

		GameEngineInput::GetInst()->CreateKey(KEY_ACTION, VK_SPACE);
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
// 액션키가 눌릴경우 True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_ACTION))
	{
		return false;
	}

	return true;
}

// 액션키가 눌리고 있을 경우
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_ACTION))
	{
		return false;
	}

	return true;
}

// 액션키가 떨어진 경우
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_ACTION))
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

	// 테스트용 코드
	if (GetCurrentLevel() == LEVEL_PLAY_LEVEL)
	{
		CurrentLevelH = SCALE_MAPBOOKS_X;
		CurrentLevelW = SCALE_MAPBOOKS_Y;
	}
	// 테스트용 코드

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

// 충돌체크
void Player::MoveCheck(float4 _MoveDir)
{
	// MoveDir은 오직 이동중에서만 갱신됨.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// TODO::컬리전맵 취득
	// GetMapColImage();


	// TODO::맵과 충돌 판정
	//float4 NextPos = GetPosition() + CheckLength;
	//float4 CheckPos = SetCheckPos(NextPos);

	//int Color = MapColImage_->GetImagePixel(CheckPos);

	// 이동
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	// 임시데이터
	PlayerAnimationChange(ANIM_KEYWORD_PLAYER_IDLE);
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

void Player::PlayerAnimationChange(std::string _Anim)
{
	std::string Dir;

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		Dir = "Left";
	}
	if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		Dir = "Right";
	}

	PlayerRenderer_->ChangeAnimation(_Anim + Dir);
}