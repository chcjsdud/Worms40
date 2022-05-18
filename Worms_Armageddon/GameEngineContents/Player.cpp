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
	// Ű����
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		// �̵�
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, VK_RIGHT);

		// ����
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_JUMP, VK_RETURN);
		// �齺���̽�
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_BACKFLIP, VK_BACK);

		// ��������
		GameEngineInput::GetInst()->CreateKey(KEY_ANGLE_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(KEY_ANGLE_DOWN, VK_DOWN);

		GameEngineInput::GetInst()->CreateKey(KEY_ACTION, VK_SPACE);
	}
}

// ������ �� Ű�� ������� True
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

// ������ �ִ� Ű�� ������� True
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
// �׼�Ű�� ������� True
bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_ACTION))
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������ ���� ���
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_ACTION))
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������ ���
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_ACTION))
	{
		return false;
	}

	return true;
}

// ������ �ʰ� �� Ű�� ������� True
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

	// �׽�Ʈ�� �ڵ�
	if (GetCurrentLevel() == LEVEL_PLAY_LEVEL)
	{
		CurrentLevelH = SCALE_MAPBOOKS_X;
		CurrentLevelW = SCALE_MAPBOOKS_Y;
	}
	// �׽�Ʈ�� �ڵ�

	// TODO::���콺 �̵��� ���� ī�޶� ��ġ�� �����ϰų�
	// TODO::�÷��̾��� ��ġ�� ���缭 ī�޶� ����ٴϰų��� 2���� ���
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	// ī�޶� �� ������ �������� ����ġ
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

	// ī�޶� ��ġ ����
	GetLevel()->SetCameraPos(CameraPos_);
}

// �浹üũ
void Player::MoveCheck(float4 _MoveDir)
{
	// MoveDir�� ���� �̵��߿����� ���ŵ�.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// TODO::�ø����� ���
	// GetMapColImage();


	// TODO::�ʰ� �浹 ����
	//float4 NextPos = GetPosition() + CheckLength;
	//float4 CheckPos = SetCheckPos(NextPos);

	//int Color = MapColImage_->GetImagePixel(CheckPos);

	// �̵�
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	// �ӽõ�����
	PlayerAnimationChange(ANIM_KEYWORD_PLAYER_IDLE);
}


// ���� ����
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


// ���� ������Ʈ
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