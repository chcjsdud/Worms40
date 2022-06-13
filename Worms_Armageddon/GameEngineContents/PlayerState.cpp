#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include "PixelCollision.h"

#pragma region Weapon
#include "Baz.h"
#include "Grenade.h"
#include "AirStrike.h"
#include "Sheep.h"
#include "SuperSheep.h"
#pragma endregion


void Player::IdleUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyUp())
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

	//IsSwitch가 false 일때만 이전상태를 받게함.
	if (!IsSwitch)
	{
		PrevWeaponState_ = WeaponState_;
	}


	if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_BAZ))
	{
		WeaponState_ = WeaponState::Baz;
		IsSwitch = true;
	}
	if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_GRENADE))
	{
		WeaponState_ = WeaponState::Grenade;
		IsSwitch = true;
	}
	if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_AIRSTRIKE))
	{
		WeaponState_ = WeaponState::AirStrike;
		IsSwitch = true;
	}
	else if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_SUPERSHEEP))
	{
		WeaponState_ = WeaponState::SuperSheep;
		IsSwitch = true;
	}

	//IsSwitch가 true 이면 무기를 스왑한것.
	if (IsSwitch == true)
	{
		StateChange(PlayerState::WeaponSwap);
	}

	// 발사 방향을 플레이어가 바라보는 방향으로 조정
	ShotAngle_.x = MoveDir_.x;

	switch (WeaponState_)
	{
		// 각도가 필요한 무기에 대해서만 각도 조절
	case WeaponState::Baz:

		// 무기 각도 조절
		MoveWeaponAngle(GameEngineTime::GetDeltaTime());
		// 무기 파워 조절
		ChargingWeaponPower();

		break;
	case WeaponState::Homing:
		break;
	case WeaponState::Mortar:
		break;
	case WeaponState::Grenade:
		break;
	case WeaponState::Axe:
		break;
	case WeaponState::Uzi:
		break;
	case WeaponState::FirePunch:
		break;
	case WeaponState::Sheep:
		break;
	case WeaponState::SuperSheep:
		break;
	case WeaponState::AirStrike:
		break;
	case WeaponState::BlowTorch:
		break;
	case WeaponState::Drill:
		break;
	case WeaponState::Grider:
		break;
	case WeaponState::None:
		break;
	default:
		break;
	}
}

void Player::WeaponSwapUpdate()
{

	if (IsSwitch == true)
	{
		switch (PrevWeaponState_)
		{
			// 각도가 필요한 무기에 대해서만 각도 조절
		case WeaponState::Baz:
			StateName_ = ANIM_KEYWORD_PLAYER_BAZOFF;
			break;
		case WeaponState::Homing:
			break;
		case WeaponState::Mortar:
			break;
		case WeaponState::Grenade:
			StateName_ = ANIM_KEYWORD_PLAYER_GRNOFF;
			break;
		case WeaponState::Axe:
			break;
		case WeaponState::Uzi:
			break;
		case WeaponState::FirePunch:
			break;
		case WeaponState::Sheep:
			break;
		case WeaponState::SuperSheep:
			StateName_ = ANIM_KEYWORD_PLAYER_SHEEPOFF;
			break;
		case WeaponState::AirStrike:
			StateName_ = ANIM_KEYWORD_PLAYER_AIROFF;
			break;
		case WeaponState::BlowTorch:
			break;
		case WeaponState::Drill:
			break;
		case WeaponState::Grider:
			break;
		case WeaponState::None:
			break;
		default:
			break;
		}

		PlayerAnimationChange(StateName_);
	}

	if (PlayerRenderer_->IsEndAnimation())
	{
		StateChange(PlayerState::Idle);
		IsSwitch = false;
	}
}




void Player::MoveUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyUp())
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
	PlayerAnimationChange(StateName_);
}

void Player::ActionUpdate()
{
	if (false == Weapon_->WeaponUpdate())
	{
		// 사용된 무기 삭제
		Weapon_->Death();

		WeaponState_ = WeaponState::None;

		StateChange(PlayerState::Idle);

		IsTurnEnd_ = true;
	}
	else
	{
		// 카메라 위치 이동용 발사체 위치 반환
		WeaponPos_ = Weapon_->GetWeaponPosition();
	}
}




void Player::JumpUpdate()
{
	JumpDelayTime_ -= GameEngineTime::GetDeltaTime();


	if (0 >= JumpDelayTime_ && IsJump_ == false)
	{
		IsJump_ = true;
		//충돌하기 전까지는 원래진행하던 방향으로 좌,우 이동
		if (CurDirName_ == PLAYER_DIR_RIGHT)
		{
			JumpMoveDir_ = float4::RIGHT * (JumpSpeed_ - 100.0f);
		}
		else
		{
			JumpMoveDir_ = float4::LEFT * (JumpSpeed_ - 100.0f);
		}

		JumpMoveDir_ += float4::UP * JumpSpeed_;
	}

	if(IsJump_==true)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_JUMP;
		PlayerAnimationChange(StateName_);



		//충돌시 좌 ,우 변경
		JumpMoveDir_ = PixelCol_->PlayerBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, JumpMoveDir_,JumpSpeed_);
			
		
		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime());

		JumpMoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 20.0f;



		//웜즈 밑부분픽셀 체크용 변수 선언
		float4 LeftPosRight = float4::LEFT;
		float4 RightPosLeft = float4::RIGHT;
		float4 LeftPos = { GetPosition().x - PLAYER_SIZE_X, GetPosition().y };
		int LeftColor = ColMapImage_->GetImagePixel(LeftPos);
		float4 RightPos = { GetPosition().x + PLAYER_SIZE_X, GetPosition().y };
		int RightColor = ColMapImage_->GetImagePixel(RightPos);

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;
		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
		int DownColor = ColMapImage_->GetImagePixel(DownPos);



		//웜즈의 밑부분이 파란색이면
		if (RGB(0, 0, 255) == DownColor)
		{
			JumpMoveDir_ = float4::ZERO;

			//체크용 
			float a = FallSpeed_;
			
			///*임시로 주석
			//do
			//{
			//	SetMove(LeftPosRight);
			//	RightPos = { GetPosition().x + PLAYER_SIZE_X, GetPosition().y };
			//	RightColor = ColMapImage_->GetImagePixel(RightPos);
			//} while (RGB(0, 0, 255) == RightColor);
			//
			//do
			//{
			//	SetMove(RightPosLeft);
			//	LeftPos = { GetPosition().x - PLAYER_SIZE_X, GetPosition().y };
			//	LeftColor = ColMapImage_->GetImagePixel(LeftPos);
			//} while (RGB(0, 0, 255) == LeftColor);*/


			//파란색이 아닐떄까지 올려준다.
			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				DownColor = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == DownColor);

			if (3000 <= FallSpeed_)
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


	if (0 >= JumpDelayTime_ && IsJump_ == false)
	{
		IsJump_ = true;
		//충돌하기 전까지는 원래진행하던 방향으로 좌,우 이동
		if (CurDirName_ == PLAYER_DIR_RIGHT)
		{
			JumpMoveDir_ = float4::LEFT * (JumpSpeed_ - 270.0f);
		}
		else
		{
			JumpMoveDir_ = float4::RIGHT * (JumpSpeed_ - 270.0f);
		}

		JumpMoveDir_ += float4::UP * JumpSpeed_;
	}
	if (IsJump_==true)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_BACKFLIP;
		PlayerAnimationChange(StateName_);



		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime());

		JumpMoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 30.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);


		//웜즈의 밑부분이 파란색이면
		if (RGB(0, 0, 255) == Color)
		{
			JumpMoveDir_ = float4::ZERO;

			//파란색이 아닐때까지 올려준다.
			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);

			//낙하데미지 FallSpeed가일정속도 이상이면 낙뎀추가
			if (1800 <= FallSpeed_)
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
	if (32 <= PlayerRenderer_->GetCurrentFrame())
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 10.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);

		//웜즈의 밑부분이 파란색이면
		if (RGB(0, 0, 255) == Color)
		{
			//파란색이 아닐때까지 올려준다.
			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);


		}

		//애니메이션이 끝나면 IdleState로 변경
		if (true == PlayerRenderer_->IsEndAnimation())
		{
			StateChange(PlayerState::Idle);
		}
	}
}



void Player::IdleStart()
{
	Crshair_->On();

	if (WeaponState_ == WeaponState::Baz)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_BAZON;
	}
	else if (WeaponState_ == WeaponState::Grenade)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_GRNON;
	}
	else if (WeaponState_ == WeaponState::AirStrike)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_AIRON;
	}
	else if (WeaponState_ == WeaponState::SuperSheep)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_SHEEPON;
	}
	else
	{
		StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
	}
	// 아무것도 안함을 시작함
	// TODO::현재 들고 있는 무기의 종류에 따라서 이미지를 변경?
	PlayerAnimationChange(StateName_);

	IsSwitch = false;
}

void Player::WeaponSwapStart()
{

}

void Player::MoveStart()
{
	// 이동을 시작함

	// 무기 파워 초기화
	ShotPower_ = 0.0f;

	// 크로스헤어 안보이게
	Crshair_->Off();
}

void Player::ActionStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
	PlayerAnimationChange(StateName_);
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
		Weapon_ = GetLevel()->CreateActor<Sheep>();
		break;
	case WeaponState::SuperSheep:
		Weapon_ = GetLevel()->CreateActor<SuperSheep>();
		//Weapon_->SetWeaponState(WeaponState_);
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
	
	// 발사각 정규화
	ShotAngle_.Normal2D();

  	Weapon_->SetPosition(this->GetPosition());
	Weapon_->SetShotDir(MoveDir_);
	Weapon_->SetShotAngle(ShotAngle_);
	Weapon_->SetShotPower(ShotPower_);
}


void Player::JumpStart()
{
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 200.0f;
	IsJump_ = false;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);
	PixelCol_->SetBounceFlgFalse();

	JumpMoveDir_ = float4::ZERO;

	Crshair_->Off();
}

//웜즈 백플립 State
void Player::BackFlipStart()
{
	IsJump_ = false;
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 300.0f;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);

	Crshair_->Off();
}

//웜즈가 너무높은곳에서 떨어졌을시 땅에 박히는 State
void Player::FalledStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_FALL;
	JumpSpeed_ = 50.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	PlayerRenderer_->ChangeAnimation(StateName_);
	JumpDelayTime_ = 1.6f;
}

void Player::FlyAwayStart()
{
	PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_FLY);
	PlayerRenderer_->SetRotationFilter(IMG_FLY_LFFT_FILTER);
	IsFly_ = true;
}


void Player::FlyAwayUpdate()
{
	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + FlyMoveDir_);
	// TODO:: ↓이거 뭔가 버그있음.
	PlayerRenderer_->SetRotationZ(Degree + 180); // 방향에 따른 투사체 각도

	SetMove(FlyMoveDir_ * GameEngineTime::GetDeltaTime());
	FlyMoveDir_.y += 10.0f;

	FlyMoveDir_ = PixelCol_->PlayerFlyBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, FlyMoveDir_, FlySpeed_);


	if (PixelCol_->GetBounceFlg())
	{
		FlySpeed_ *= 0.5f;
	}


	float4 DownPos = GetPosition() + float4{0,PLAYER_SIZE_Y / 2};
	float4 DownLeftPos = GetPosition() + float4{ -PLAYER_SIZE_X/2,PLAYER_SIZE_Y / 2 };
	float4 DownRightPos = GetPosition() + float4{ PLAYER_SIZE_X/2,PLAYER_SIZE_Y / 2 };

	int DownColor = ColMapImage_->GetImagePixel(DownPos);
	int DownLeftColor = ColMapImage_->GetImagePixel(DownLeftPos);
	int DownRightColor = ColMapImage_->GetImagePixel(DownRightPos);

	if (RGB(0, 0, 255) == DownColor &&
		RGB(0,0,255)== DownLeftColor &&
		RGB(0,0,255)==DownRightColor)
	{
		PlayerRenderer_->SetRotationZ(0);
		do
		{
			SetMove(float4::UP);
			DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
			DownColor = ColMapImage_->GetImagePixel(DownPos);
		} while (RGB(0, 0, 255) == DownColor);


		//너무높은곳에서 떨어지면
		if (FlyMoveDir_.y >= 500.0f)
		{
			StateChange(PlayerState::Falled);
			IsDamaged_ = false;
			IsFly_ = false;
		}



	}

	///마지막에 IsTrunEnd =true;
	///IsDamaged = true;
}