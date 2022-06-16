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



	if (ControlFlg_ == true)
	{
		// �׼��� �̵����� �켱������ ����.
		if (true == IsActionKeyUp())
		{
			ControlWorms_->Off();
			CrgBlob_->DeActivate();
			Crshair_->Off();
			StateChange(PlayerState::Action);
			return;
		}
		// �̵�Ű�� ������ �̵�
		if (true == IsMoveKeyDown())
		{
			StateChange(PlayerState::Move);
			return;
		}
		//����Ű ������ ����
		if (true == IsJumpKeyDown())
		{
			StateChange(PlayerState::Jump);
			return;
		}

		if (true == IsPlayerDeathKeyDown())
		{
			StateChange(PlayerState::Death);
			return;
		}


		//���ø�
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

		//IsSwitch�� false �϶��� �������¸� �ް���.
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
		if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_SHEEP))
		{
			WeaponState_ = WeaponState::Sheep;
			IsSwitch = true;
		}
		if (GameEngineInput::GetInst()->IsDown(KEY_WEAPON_SUPERSHEEP))
		{
			WeaponState_ = WeaponState::SuperSheep;
			IsSwitch = true;
		}

		//IsSwitch�� true �̸� ���⸦ �����Ѱ�.
		if (IsSwitch == true)
		{
			StateChange(PlayerState::WeaponSwap);
		}

		// �߻� ������ �÷��̾ �ٶ󺸴� �������� ����
		ShotAngle_.x = MoveDir_.x;

		switch (WeaponState_)
		{
			// ������ �ʿ��� ���⿡ ���ؼ��� ���� ����
		case WeaponState::Baz:

			// ���� ���� ����
			MoveWeaponAngle(GameEngineTime::GetDeltaTime());
			// ���� �Ŀ� ����
			ChargingWeaponPower();

			break;
		case WeaponState::Homing:
			break;
		case WeaponState::Mortar:
			break;
		case WeaponState::Grenade:
			// ���� ���� ����
			MoveWeaponAngle(GameEngineTime::GetDeltaTime());
			// ���� �Ŀ� ����
			ChargingWeaponPower();
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
}

void Player::WeaponSwapUpdate()
{

	if (IsSwitch == true)
	{
		switch (PrevWeaponState_)
		{
			// ������ �ʿ��� ���⿡ ���ؼ��� ���� ����
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
			StateName_ = ANIM_KEYWORD_PLAYER_SHEEPOFF;
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
			StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
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
	// �׼��� �̵����� �켱������ ����.
	if (true == IsActionKeyUp())
	{
		Sound_Walk.Stop();
		StateChange(PlayerState::Action);
		return;
	}
	// Ű�� ����������� Idle���·� ��ȯ
	if (true == IsMoveKeyUp() && false == IsMoveKeyPress())
	{
		Sound_Walk.Stop();
		StateChange(PlayerState::Idle);
		return;
	}


	// �̵� ���¿��� ����
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

	//����Ű ������ ����
	if (true == IsJumpKeyDown())
	{
		Sound_Walk.Stop();
		StateChange(PlayerState::Jump);
		return;
	}

	//���ø�
	if (true == IsBackFlipKeyDown())
	{
		KeyCount_++;
		if (2 <= KeyCount_)
		{
			KeyCount_ = 0;
			Sound_Walk.Stop();
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
		// ���� ���� ����
		// Weapon_->Death();
		ShotPower_ = WEAPON_DEFAULT_SHOT_POWER;
		WeaponState_ = WeaponState::None;

		StateChange(PlayerState::Idle);

		IsTurnEnd_ = true;
	}
	else
	{
		// ī�޶� ��ġ �̵��� �߻�ü ��ġ ��ȯ
		WeaponPos_ = Weapon_->GetWeaponPosition();
	}
}




void Player::JumpUpdate()
{
	JumpDelayTime_ -= GameEngineTime::GetDeltaTime();


	if (0 >= JumpDelayTime_ && IsJump_ == false)
	{
		IsJump_ = true;
		//�浹�ϱ� �������� ���������ϴ� �������� ��,�� �̵�
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

		// ����
		if (false == Sound_JumpOn)
		{
			Sound_Jump = GameEngineSound::SoundPlayControl("jump1.wav");
			Sound_Jump.Volume(SND_VOL_JUMP);
			Sound_JumpOn = true;
		}

		//�浹�� �� ,�� ����
		JumpMoveDir_ = PixelCol_->PlayerBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, JumpMoveDir_,JumpSpeed_);
			
		
		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime());

		JumpMoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 20.0f;



		//���� �غκ��ȼ� üũ�� ���� ����
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



		//������ �غκ��� �Ķ����̸�
		if (RGB(0, 0, 255) == DownColor)
		{
			JumpMoveDir_ = float4::ZERO;

			//üũ�� 
			float a = FallSpeed_;
			
			///*�ӽ÷� �ּ�
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


			//�Ķ����� �ƴҋ����� �÷��ش�.
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

			//���� ���߿� Ű�� ������������ �ٷ� �����̰� ������ش�.
			if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT) ||
				true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
			{
				StateChange(PlayerState::Move);
			}
			else
			{
				//Ű�� ���� Idle���·�
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
		//�浹�ϱ� �������� ���������ϴ� �������� ��,�� �̵�
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

		// ����
		if (false == Sound_BackflipOn)
		{
			Sound_Backflip = GameEngineSound::SoundPlayControl("backflip.wav");
			Sound_Backflip.Volume(SND_VOL_BACKFLIP);
			Sound_BackflipOn = true;
		}

		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime());

		JumpMoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 30.0f;

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
		int Color = ColMapImage_->GetImagePixel(DownPos);


		//������ �غκ��� �Ķ����̸�
		if (RGB(0, 0, 255) == Color)
		{
			JumpMoveDir_ = float4::ZERO;

			//�Ķ����� �ƴҶ����� �÷��ش�.
			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);

			//���ϵ����� FallSpeed�������ӵ� �̻��̸� �����߰�
			if (1800 <= FallSpeed_)
			{
				StateChange(PlayerState::Falled);
				return;
			}

			//���� ���߿� Ű�� ������������ �ٷ� �����̰� ������ش�.
			if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT) ||
				true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
			{
				StateChange(PlayerState::Move);
			}
			else
			{
				//Ű�� ���� Idle���·�
				StateChange(PlayerState::Idle);
			}
		}
	}
}

//TODO : �ణ�� �̻����� ����
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

		//������ �غκ��� �Ķ����̸�
		if (RGB(0, 0, 255) == Color)
		{
			//�Ķ����� �ƴҶ����� �÷��ش�.
			do
			{
				SetMove(UpPos);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				Color = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == Color);


		}

		//�ִϸ��̼��� ������ IdleState�� ����
		if (true == PlayerRenderer_->IsEndAnimation())
		{
			WeaponState_ = WeaponState::None;
			StateChange(PlayerState::Idle);
		}
	}
}



void Player::IdleStart()
{


	if (Damage_ != 0)
	{
		PlayerHp_ -= Damage_;
		//Hp�� 0���� ������ 0����
		if (PlayerHp_ <= 0)
		{
			PlayerHp_ = 0;
		}

		Damage_ = 0;

		// HP UI�� ǥ�õ� HP����
		Hpbar_->ChangeHpBarFont(PlayerHp_);
	}


	if (WeaponState_ != WeaponState::None)
	{
		Crshair_->On();
	}
	else
	{
		Crshair_->Off();
	}

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
	else if (WeaponState_ == WeaponState::Sheep)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_SHEEPON;
	}
	else if (WeaponState_ == WeaponState::SuperSheep)
	{
		StateName_ = ANIM_KEYWORD_PLAYER_SHEEPON;
	}
	else
	{
		if (PlayerHp_ <= 40)
		{
			StateName_ = ANIM_KEYWORD_PLAYER_BREATH;
		}
		else
		{
			StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
		}
	}
	// �ƹ��͵� ������ ������
	// TODO::���� ��� �ִ� ������ ������ ���� �̹����� ����?
	PlayerAnimationChange(StateName_);

	IsSwitch = false;
}

void Player::WeaponSwapStart()
{

}

void Player::MoveStart()
{
	// �ȴ� ����
	Sound_Walk = GameEngineSound::SoundPlayControl("Walk-ExpandCompress.wav", 100);
	Sound_Walk.Volume(SND_VOL_WALK);
	// �̵��� ������

	// ���� �Ŀ� �ʱ�ȭ
	ShotPower_ = 0.0f;	// ũ�ν���� �Ⱥ��̰�
	Crshair_->Off();
}

void Player::ActionStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_IDLE;
	PlayerAnimationChange(StateName_);
	// ���� ���� ����
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
		Weapon_->SetTeamColor(MyTeamColor_);
		break;
	case WeaponState::Axe:
		break;
	case WeaponState::Uzi:
		break;
	case WeaponState::FirePunch:
		break;
	case WeaponState::Sheep:
		Weapon_ = GetLevel()->CreateActor<Sheep>();
		Weapon_->SetTeamColor(MyTeamColor_);
		break;
	case WeaponState::SuperSheep:
		Weapon_ = GetLevel()->CreateActor<SuperSheep>();
		Weapon_->SetTeamColor(MyTeamColor_);
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
		// �⺻�� ����ī
		Weapon_ = GetLevel()->CreateActor<Baz>();
		break;
	}
	
	// �߻簢 ����ȭ
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

//���� ���ø� State
void Player::BackFlipStart()
{
	IsJump_ = false;
	JumpDelayTime_ = 0.5f;
	JumpSpeed_ = 300.0f;
	StateName_ = ANIM_KEYWORD_PLAYER_JUMPRDY;
	PlayerAnimationChange(StateName_);

	Crshair_->Off();
}

//��� �ʹ����������� ���������� ���� ������ State
void Player::FalledStart()
{
	StateName_ = ANIM_KEYWORD_PLAYER_FALL;
	JumpSpeed_ = 50.0f;
	MoveDir_ = float4::UP * JumpSpeed_;
	PlayerAnimationChange(StateName_);
	JumpDelayTime_ = 1.6f;

	// Fall ����
	Sound_Fall = GameEngineSound::SoundPlayControl("fall.wav");
	Sound_Fall.Volume(SND_VOL_FALL);
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

	PlayerRenderer_->SetRotationZ(Degree + 180); // ���⿡ ���� ����ü ����

	SetMove(FlyMoveDir_ * GameEngineTime::GetDeltaTime());
	FlyMoveDir_.y += 10.0f;

	
	FlyMoveDir_ = PixelCol_->PlayerFlyBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, ColMapImage_, FlyMoveDir_, FlySpeed_);




	float4 DownPos = GetPosition() + float4{0,PLAYER_SIZE_Y / 2};
	float4 DownLeftPos = GetPosition() + float4{ -PLAYER_SIZE_X / 2,PLAYER_SIZE_Y / 2 };
	float4 DownRightPos = GetPosition() + float4{ PLAYER_SIZE_X / 2,PLAYER_SIZE_Y / 2 };
	float4 LeftPos = GetPosition() + float4{ -PLAYER_SIZE_X / 2,0 };
	float4 RightPos = GetPosition() + float4{ PLAYER_SIZE_X / 2 ,0 };

	int DownColor = ColMapImage_->GetImagePixel(DownPos);
	int DownLeftColor = ColMapImage_->GetImagePixel(DownLeftPos);
	int DownRightColor = ColMapImage_->GetImagePixel(DownRightPos);
	int LeftColor = ColMapImage_->GetImagePixel(LeftPos);
	int RightColor = ColMapImage_->GetImagePixel(RightPos);




	if (RGB(0, 0, 255) == DownColor)
	{
		if (FlyMoveDir_.y >= 500.0f)
		{
			PlayerRenderer_->SetRotationZ(0);
			do
			{
				SetMove(float4::UP);
				DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
				DownColor = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == DownColor);


			//�ʹ����������� ��������
			StateChange(PlayerState::Falled);
			Damage_ += 10;
			IsDamaged_ = false;
			IsFly_ = false;
		}
	}

	if (RGB(0, 0, 255) == DownColor && RGB(0, 0, 255) == DownRightColor)
	{
		//��簡 ���ϴٸ� ������ȯ  
		if (FlyMoveDir_.x >= 0 && RGB(0,0,255) == RightColor)
		{
			FlyMoveDir_.x *= -1.0f;
			MoveDir_ = float4::LEFT;
		}
		else
		{
			MoveDir_ = float4::RIGHT;
		}

		if (FlyMoveDir_.x < 0)
		{
			MoveDir_ = float4::LEFT;
		}

		StateChange(PlayerState::Slide);
		return;
			
	}
	else if (RGB(0, 0, 255) == DownColor && RGB(0, 0, 255) == DownLeftColor)
	{
		if (FlyMoveDir_.x <= 0 && RGB(0, 0, 255) == LeftColor)
		{
			FlyMoveDir_.x *= -1.0f;
			MoveDir_ = float4::RIGHT;
		}
		else
		{
			MoveDir_ = float4::LEFT;
		}

		if (FlyMoveDir_.x >= 0)
		{
			MoveDir_ = float4::RIGHT;
		}
		StateChange(PlayerState::Slide);
		return;
	}


	///�������� IsTrunEnd =true;
	///IsDamaged = true;
}


void Player::DeathStart()
{
	Sound_Byebye = GameEngineSound::SoundPlayControl("byebye.wav");
	Sound_Byebye.Volume(SND_VOL_BYEBYE);

	PlayerAnimationChange(ANIM_KEYWORD_PLAYER_DEATH);
	PlayerHp_ = 0;
	JumpSpeed_ = 100.0f;
	JumpMoveDir_ = float4::UP;
	Hpbar_->ChangeHpBarFont(PlayerHp_);
	Crshair_->Off();
	CrgBlob_->DeActivate();
	ControlWorms_->Off();

}

void Player::DeathUpdate()
{

	//�÷��̾ �����̵Ǹ�
	if (IsGrave_ == true)
	{
		//���� ���� Ƣ��ö��ٰ� ��������
		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime() * JumpSpeed_);
		JumpSpeed_ -= 10.0f;

		float4 DownPos = GetPosition() + float4{ 0, 2.0f };
		int DownColor = ColMapImage_->GetImagePixel(DownPos);

		//����������
		if (RGB(0, 0, 255) == DownColor)
		{
			do
			{
				SetMove(float4::UP);
				DownPos = { GetPosition().x, GetPosition().y + 2.0f };
				DownColor = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == DownColor);

			//State�� None���κ���
			StateChange(PlayerState::None);
			IsDeath_ = true;
		}

		return;
	}

	//�����ϴ� �ִϸ��̼��̳����� �������� ����
	if (PlayerRenderer_->IsEndAnimation() == true)
	{
		PlayerRenderer_->ChangeAnimation(ANIM_KEYWORD_PLAYER_GRAVE);
		IsGrave_ = true;
	}


}



void Player::SlideStart()
{
	PlayerRenderer_->SetRotationZ(0);
	PlayerAnimationChange(ANIM_KEYWORD_PLAYER_SLIDE);
	IsDamaged_ = false;
	IsFly_ = false;

	FlyMoveDir_.y = 0;
	SlideEnd_ = false;
	IsFall_ = false;
	
}

void Player::SlideUpdate()
{

	if (SlideEnd_ == true)
	{
		PlayerAnimationChange(ANIM_KEYWORD_PLAYER_SLIDE_UP);

		if (PlayerRenderer_->IsEndAnimation())
		{
			SlideEnd_ = false;
			StateChange(PlayerState::Idle);
		}
		return;
	}

	float4 DownPos = GetPosition() + float4{ 0,PLAYER_SIZE_Y / 2 };
	float4 DownLeftPos = GetPosition() + float4{ -PLAYER_SIZE_X / 2,PLAYER_SIZE_Y / 2 };
	float4 DownRightPos = GetPosition() + float4{ PLAYER_SIZE_X / 2,PLAYER_SIZE_Y / 2 };
	float4 LeftPos = GetPosition() + float4{ -PLAYER_SIZE_X / 2,0 };
	float4 RightPos = GetPosition() + float4{ PLAYER_SIZE_X / 2 ,0 };

	int DownColor = ColMapImage_->GetImagePixel(DownPos);
	int DownLeftColor = ColMapImage_->GetImagePixel(DownLeftPos);
	int DownRightColor = ColMapImage_->GetImagePixel(DownRightPos);
	int LeftColor = ColMapImage_->GetImagePixel(LeftPos);
	int RightColor = ColMapImage_->GetImagePixel(RightPos);


	if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		if (RGB(0, 0, 255) == RightColor)
		{
			do
			{
				SetMove(float4::LEFT);
				RightPos = { GetPosition().x + 12.0f, GetPosition().y };
				RightColor = ColMapImage_->GetImagePixel(RightPos);
			} while (RGB(0, 0, 255) == RightColor);
			
			FlyMoveDir_.x *= -1.0f;
			MoveDir_ = float4::LEFT;
			PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_SLIDE_LEFT);
		}
	}
	else
	{
		if (RGB(0, 0, 255) == LeftColor)
		{
			do
			{
				SetMove(float4::RIGHT);
				LeftPos = { GetPosition().x - 12.0f, GetPosition().y };
				LeftColor = ColMapImage_->GetImagePixel(LeftPos);
			} while (RGB(0, 0, 255) == LeftColor);
			
			FlyMoveDir_.x *= -1.0f;
			MoveDir_ = float4::RIGHT;
			PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_SLIDE_RIGHT);
		}
	}
	
	if (IsFall_ == false)
	{
		FlyMoveDir_.x *= 0.9f;
	}

	SetMove(FlyMoveDir_ * GameEngineTime::GetDeltaTime());

	//MoveFall();
	//�߷�
	float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;
	float4 NextPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
	int Color = ColMapImage_->GetImagePixel(NextPos);

	if (RGB(0, 0, 255) != Color)
	{
		FallLength_ += SlideFallspeed_ * GameEngineTime::GetDeltaTime();
		SlideFallspeed_ += 50.0f * GameEngineTime::GetDeltaTime();

		// �ִ� ���ϼӵ�
		if (SlideFallspeed_ >= 600.0f)
		{
			SlideFallspeed_ = 600.0f;
		}

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * SlideFallspeed_);
	}
	else
	{

		SlideFallspeed_ = 400.0f;
	}

	//
	if (FlyMoveDir_.x <= 0.01 && FlyMoveDir_.x >= -0.01 && IsFall_== false)
	{
		FlyMoveDir_ = float4::ZERO;
		SlideEnd_ = true;
	}
	else
	{
		/*if (RGB(0, 0, 255) != DownColor)
		{
			do
			{
				SetMove(float4::DOWN * GameEngineTime::GetDeltaTime());
				DownPos = { GetPosition().x, GetPosition().y  + 2.0f };
				DownColor = ColMapImage_->GetImagePixel(DownPos);

			} while (RGB(0, 0, 255) != DownColor);
		}*/
		/*if (RGB(0, 0, 255) == DownColor && IsFall_ == false)
		{
			do
			{
				SetMove(float4::UP);
				DownPos = { GetPosition().x , GetPosition().y + 12.0f };
				DownColor = ColMapImage_->GetImagePixel(DownPos);
			} while (RGB(0, 0, 255) == DownColor);
		}*/
	}



}