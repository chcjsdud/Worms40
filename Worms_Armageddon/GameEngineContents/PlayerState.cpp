#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include "PixelCollision.h"

#pragma region Weapon
#include "Baz.h"
#include "Grenade.h"
#include "AirStrike.h"
#pragma endregion


void Player::IdleUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	// 이동키가 눌리면 이동
	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}
	//점프키 눌리면 점프
	if (true == IsJumpKeyDown())
	{
		StateChange(PlayerState::Jump);
		return;
	}


	//백플립
	if (true == IsBackFlipKeyDown())
	{
		KeyCount_++;
		if (2 <=KeyCount_)
		{
			KeyCount_ = 0;
			StateChange(PlayerState::BackFlip);
			return;
		}
	}
	else if (true == IsBackFlipKeyFree())
	{
		KeyTimer_ -= GameEngineTime::GetDeltaTime();
		if (0 >= KeyTimer_)
		{
			KeyTimer_ = 0.5f;
			KeyCount_ = 0;
		}
		if (true == IsBackFlipKeyDown())
		{
			KeyCount_++;
		}
	}

	if (GameEngineInput::GetInst()->IsPress(KEY_WEAPON_BAZ))
	{
		WeaponState_ = WeaponState::Baz;
	}
	if (GameEngineInput::GetInst()->IsPress(KEY_WEAPON_GRENADE))
	{
		WeaponState_ = WeaponState::Grenade;
	}
	if (GameEngineInput::GetInst()->IsPress(KEY_WEAPON_AIRSTRIKE))
	{
		WeaponState_ = WeaponState::AirStrike;
	}

	MoveFall();

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
		StateName_ = ANIM_KEYWORD_PLAYER_WALK;
		CurDirName_ = PLAYER_DIR_RIGHT;
		MoveCheck(float4::RIGHT);
		
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		StateName_ = ANIM_KEYWORD_PLAYER_WALK;
		CurDirName_ = PLAYER_DIR_LEFT;
		MoveCheck(float4::LEFT);

	}

	//점프키 눌리면 점프
	if (true == IsJumpKeyDown())
	{
		StateChange(PlayerState::Jump);
		return;
	}

	//백플립
	if (true == IsBackFlipKeyDown())
	{
		KeyCount_++;
		if (2 <= KeyCount_)
		{
			KeyCount_ = 0;
			StateChange(PlayerState::BackFlip);
			return;
		}
	}
	else if (true == IsBackFlipKeyFree())
	{
		KeyTimer_ -= GameEngineTime::GetDeltaTime();
		if (0 >= KeyTimer_)
		{
			KeyTimer_ = 0.5f;
			KeyCount_ = 0;
		}
		if (true == IsBackFlipKeyDown())
		{
			KeyCount_++;
		}
	}

	MoveFall();
	PlayerAnimationChange(StateName_);
}

void Player::ActionUpdate()
{
	if (false == Weapon_->WeaponUpdate())
	{
		// TODO::동작이 끝날경우에 Idle로 전환
		StateChange(PlayerState::Idle);

		// TODO::몇초간 이동한 후에 턴 종료되도록 수정
		IsTurnEnd_ = true;
	}
	else
	{
		// 카메라 위치 이동용 발사체 위치 반환
		WeaponPos_ = Weapon_->GetPosition();
	}
}

void Player::JumpUpdate()
{
	JumpDelayTime_ -= GameEngineTime::GetDeltaTime();
	if (0 >= JumpDelayTime_)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_JUMP;
		PlayerAnimationChange(StateName_);

		if (!PixelCol_->GetBounceFlg())
		{
			JumpMoveDir_ = PixelCol_->PlayerBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, JumpMoveDir_);
			MoveDir_ = PixelCol_->PlayerBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, MoveDir_);
		}


		if (CurDirName_ == PLAYER_DIR_RIGHT)
		{
			JumpMoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
			SetMove(JumpMoveDir_);
		}
		else
		{
			JumpMoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 100.0f;
			SetMove(JumpMoveDir_);
		}


		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 20.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);

		


		if (RGB(0, 0, 255) == Color)
		{
			MoveDir_ = float4::ZERO;
			JumpMoveDir_ = float4::ZERO;

			float a = FallSpeed_;

			do
			{
				SetMove(UpPos); 
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);

			if (1500 <= FallSpeed_)
			{
				StateChange(PlayerState::Falled);
				return;
			}

			//점프 도중에 키를 누르고있으면 바로 움직이게 만들어준다.
			if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT) ||
				true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
			{
				StateChange(PlayerState::Move);
			}
			else
			{
				//키를 때면 Idle상태로
				StateChange(PlayerState::Idle);
			}
		}
	}
}

void Player::BackFlipUpdate()
{
	JumpDelayTime_ -= GameEngineTime::GetDeltaTime();
	if (0 >= JumpDelayTime_)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_BACKFLIP;
		PlayerAnimationChange(StateName_);

		if (CurDirName_ == PLAYER_DIR_RIGHT)
		{
			JumpMoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 20.0f;
			SetMove(JumpMoveDir_);
		}
		else
		{
			JumpMoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 20.0f;
			SetMove(JumpMoveDir_);
		}


		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 30.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);

		if (RGB(0, 0, 255) == Color)
		{
			MoveDir_ = float4::ZERO;
			JumpMoveDir_ = float4::ZERO;

			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);

			//낙하데미지
			if (2000 <= FallSpeed_)
			{
				StateChange(PlayerState::Falled);
				return;
			}

			//점프 도중에 키를 누르고있으면 바로 움직이게 만들어준다.
			if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT) ||
				true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
			{
				StateChange(PlayerState::Move);
			}
			else
			{
				//키를 때면 Idle상태로
				StateChange(PlayerState::Idle);
			}
		}
	}
}

//TODO : 약간의 이상한점 수정
void Player::FalledUpdate()
{
	if(32 <= PlayerRenderer_->GetCurrentFrame())
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 10.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);

		if (RGB(0, 0, 255) == Color)
		{
			MoveDir_ = float4::ZERO;
			JumpMoveDir_ = float4::ZERO;


			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);

			
		}
		if (true == PlayerRenderer_->IsEndAnimation())
		{
			StateChange(PlayerState::Idle);
		}
	}
}



void Player::IdleStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
	// 아무것도 안함을 시작함
	// TODO::현재 들고 있는 무기의 종류에 따라서 이미지를 변경?
	PlayerAnimationChange(StateName_);
}

void Player::MoveStart()
{
	// 이동을 시작함
}

void Player::ActionStart()
{
	// 무기 액터 생성
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
		Weapon_ = GetLevel()->CreateActor<AirStrike>();
		break;
	case WeaponState::BlowTorch:
		break;
	case WeaponState::Drill:
		break;
	case WeaponState::Grider:
		break;
	default:
		// 기본값 바주카
		Weapon_ = GetLevel()->CreateActor<Baz>();
		break;
	}

	Weapon_->SetPosition(this->GetPosition());
	Weapon_->SetShotDir(MoveDir_);
}

void Player::JumpStart()
{
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 200.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);
}

void Player::BackFlipStart()
{
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 300.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);
}

void Player::FalledStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_FALL;
	JumpSpeed_ = 50.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	PlayerRenderer_->ChangeAnimation(StateName_);
	JumpDelayTime_ = 1.6f;
}