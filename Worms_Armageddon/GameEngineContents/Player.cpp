#include "Player.h"
#include "PixelCollision.h"
#include "WeaponMaster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineRandom.h>

GameEngineRandom Player::Ran;
WeaponMaster* Player::Weapon_ = nullptr;

Player::Player()
	: Speed_(PLAYER_SPEED)
	, FallSpeed_(PLAYER_SPEED_FALL)
	, FallLength_(0.0f)
	, MoveDir_(float4::ZERO)
	, PlayerRenderer_(nullptr)
	, PlayerHp_(100)
	, IsDeath_(false)
	, JumpDelayTime_(0.5f)
	, IsTurnEnd_(false)
	, ShotAngle_(WEAPON_DEFAULT_SHOT_ANGLE)
	, ShotAngleMin_(WEAPON_MIN_SHOT_ANGLE)
	, ShotAngleMax_(WEAPON_MAX_SHOT_ANGLE)
	, ShotPower_(WEAPON_DEFAULT_SHOT_POWER)
	, KeyCount_(0)
	, KeyTimer_(0.5f)
	, IsJump_(false)
	, IsSwitch(false)
	, Hpbar_(nullptr)
	, Len_(0.0f)
	, ControlFlg_(false)
	, AllDamage_(0)
	, IsDamaged_(false)
	, IsDamagedCam_(false)
	, ControlWorms_(nullptr)
	, FlySpeed_(0.0f)
	, IsFly_(false)
	, IsGrave_(false)
	, WeaponState_(WeaponState::None)
	, ColMapImage_(nullptr)
	, CrgBlob_(nullptr)
	, Crshair_(nullptr)
	//, CurrentState_(PlayerState::None) �ʱ�ȭ �ϸ� �÷��̾� ���� �̻�����
	//, PrevState_(PlayerState::None)
	, JumpSpeed_(0.f)
	, MyTeamColor_(TeamColor::Max)
	, PixelCol_(nullptr)
	, PrevWeaponState_(WeaponState::None)
	, UnControlState_(PlayerUnControlState::UncontrolIdle)
	, WeaponType_(0)
	, Damage_(0)
	, SlideEnd_(false)
	, DeathDelayTime_(1.0f)
	, SlideFallspeed_(400.0f)
{
}

Player::~Player()
{
}

void Player::Start()
{
	//�ӽ� DirName �ʱⰪ
	DirName_ = ANIM_KEYWORD_DIR_LEFT;

	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();

	PlayerAnimationInit();
	PlayerKeyInit();

	int num = Ran.RandomInt(0, 1);

	if (num == 0)
	{
		PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_IDLE_RIGHT);
		MoveDir_ = float4::RIGHT;
	}
	else
	{
		PlayerRenderer_->ChangeAnimation(ANIM_NAME_PLAYER_IDLE_LEFT);
		MoveDir_ = float4::LEFT;
	}

	// �׽�Ʈ �ӽ� ������
	ColMapImage_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);

	// ũ�ν����
	Crshair_ = GetLevel()->CreateActor<Crosshair>((int)ActorGroup::UI);

	CrgBlob_ = GetLevel()->CreateActor<ChargeBlob>((int)ActorGroup::UI);
}

void Player::Update()
{

	//�÷��̾��� State�� None�̸� �̹� �׾ �����̵ǰ� IsDeath_== true�� ����.
	if (CurrentState_ == PlayerState::None)
	{
		return;
	}


	Hpbar_->HpBarSetPosition({ this->GetPosition().x , this->GetPosition().y - 25.f});
	
	//�������� �Ծ��ٸ� , IsDamged==true , Damaged�Լ����� ó��.
	if (IsFly_ == true)
	{
		FlyAwayUpdate();
		return;
	}

	CheckDeath();

	if (IsDamaged_ == true)
	{
		StateChange(PlayerState::FlyAway);
	}

	if (IsDeath_ == false)
	{
		StateUpdate();
	}
	
	if(IsDeath_==true)
	{
		DeathUpdate();
	}

	// ��Ʈ�ѵǰ� ���� ���� �÷��̾� ĳ���ʹ� �ǰ��������� ���۸� ����
	if (this->GetPlayerState() == PlayerState::Idle
		|| this->GetPlayerState() == PlayerState::Move)
	{
		MoveFall();
	}

	//Weapon�� �����ǰ� ������� �����ߴٸ�
	//if (Weapon_ != nullptr && Weapon_->GetExplodEndFlg() == true)
	//{
	//	Damaged(Weapon_->GetWeaponPosition());
	//}

	// ��Ʈ�ѵǰ� ���� ���� ĳ���ʹ� �������� �޴��� ���� ������ ����
}

void Player::Render()
{	
}

bool Player::ControllUpdate()
{
	// State���ο��� ������ �÷��׸� �����ָ� ������
	//IsTurnEnd_ = false;


	if (IsDeath_ == true)
	{
		IsTurnEnd_ = true;
		ControlWorms_->Off();
		CrgBlob_->DeActivate();
		Crshair_->Off();
		return IsTurnEnd_;
	}


	if (IsDamaged_ == true)
	{
		IsTurnEnd_ = true;
		ControlWorms_->Off();
		CrgBlob_->DeActivate();
		Crshair_->Off();
		return IsTurnEnd_;
	}

	if (ControlWorms_ != nullptr && ControlFlg_ == true)
	{
		ControlWorms_->On();
	}

	if (ControlWorms_ != nullptr && IsTurnEnd_ == true)
	{
		ControlWorms_->Off();
		Crshair_->Off();
		CrgBlob_->DeActivate();
	}

	return IsTurnEnd_;
}




void Player::PlayerAnimationInit()
{
	PlayerRenderer_ = CreateRenderer((int)RenderOrder::Player);

	//idle
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_RIGHT, ANIM_NAME_PLAYER_IDLE_RIGHT, 0, 5, 0.1f, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_LEFT, ANIM_NAME_PLAYER_IDLE_LEFT, 0, 5, 0.1f, true);


	//hp <50 idle
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BREATH_LEFT, ANIM_NAME_PLAYER_BREATH_LEFT, 0, 12, 0.05f, true , true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BREATH_RIGHT, ANIM_NAME_PLAYER_BREATH_RIGHT, 0, 12, 0.05f, true , true);

	// ���� �ִϸ��̼�
	//����ī
	PlayerRenderer_->CreateAnimation(IMG_BAZ_ON_LEFT, ANIM_NAME_BAZ_ON_LEFT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_ON_RIGHT, ANIM_NAME_BAZ_ON_RIGHT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_OFF_LEFT, ANIM_NAME_BAZ_OFF_LEFT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_OFF_RIGHT, ANIM_NAME_BAZ_OFF_RIGHT, 0, 5, 0.03f, false);

	//����ź
	PlayerRenderer_->CreateAnimation(IMG_GRN_ON_LEFT, ANIM_NAME_GRN_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_ON_RIGHT, ANIM_NAME_GRN_ON_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_OFF_LEFT, ANIM_NAME_GRN_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_OFF_RIGHT, ANIM_NAME_GRN_OFF_RIGHT, 0, 9, 0.03f, false);

	//���Ʈ����ũ
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_OFF_LEFT, ANIM_NAME_AIRSTRIKE_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_ON_LEFT, ANIM_NAME_AIRSTRIKE_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_OFF_RIGHT, ANIM_NAME_AIRSTRIKE_OFF_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_ON_RIGHT, ANIM_NAME_AIRSTRIKE_ON_RIGHT, 0, 9, 0.03f, false);
	//����ź
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_OFF_LEFT, ANIM_NAME_SHEEP_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_ON_LEFT, ANIM_NAME_SHEEP_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_OFF_RIGHT, ANIM_NAME_SHEEP_OFF_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_ON_RIGHT, ANIM_NAME_SHEEP_ON_RIGHT, 0, 9, 0.03f, false);

	// �¿� �ȴ� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WALK_LEFT, ANIM_NAME_PLAYER_WALKLEFT, 0, 14, 0.015f, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WALK_RIGHT, ANIM_NAME_PLAYER_WALKRIGHT, 0, 14, 0.015f, true);

	//���� �� �غ��� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_JUMPRDY_LEFT, ANIM_NAME_PLAYER_JUMPRDY_LEFT, 0, 9, 0.05f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_JUMPRDY_RIGHT, ANIM_NAME_PLAYER_JUMPRDY_RIGHT, 0, 9, 0.05f, false);

	//���� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FLYLINK_LEFT, ANIM_NAME_PLAYER_JUMPLEFT, 0, 6, 0.1f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FLYLINK_RIGHT, ANIM_NAME_PLAYER_JUMPRIGHT, 0, 6, 0.1f, false);

	//���ø� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BACKFLIP_LEFT, ANIM_NAME_PLAYER_BACKFLIP_LEFT, 0, 21, 0.02f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BACKFLIP_RIGHT, ANIM_NAME_PLAYER_BACKFLIP_RIGHT, 0, 21, 0.02f, false);

	//���� �ִϸ��̼�
	//33��° �̹����� �ö󰡰�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FALL_LEFT, ANIM_NAME_PLAYER_FALL_LEFT, 0, 48, 0.05f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FALL_RIGHT, ANIM_NAME_PLAYER_FALL_RIGHT, 0, 48, 0.05f, false);


	//���� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_DIE_LEFT, ANIM_NAME_PLAYER_DEATH_LEFT, 0, 59, 0.02f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_DIE_RIGHT, ANIM_NAME_PLAYER_DEATH_RIGHT, 0, 59, 0.02f, false);

	//���� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_GRAVE, ANIM_NAME_PLAYER_GRAVE, 0, 19, 0.04f, true,true);

	//���󰡴� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_FLY_LEFT, ANIM_NAME_PLAYER_FLY, 0, 0, 0, false);

	//�¸� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WIN_LEFT, ANIM_NAME_PLAYER_WIN_LEFT, 0, 13, 0.2f, true,true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WIN_RIGHT, ANIM_NAME_PLAYER_WIN_RIGHT, 0, 13, 0.2f, true,true);
	//�̲������� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_SLIDE_LEFT, ANIM_NAME_PLAYER_SLIDE_LEFT, 0, 2, 0.1f, true, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_SLIDE_RIGHT, ANIM_NAME_PLAYER_SLIDE_RIGHT, 0, 2, 0.1f, true, true);
	//�̲������� �ִϸ��̼ǿ��� �Ͼ�� �ִϸ��̼�
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_SLIDE_UP_LEFT, ANIM_NAME_PLAYER_SLIDE_UP_LEFT, 0, 35, 0.02f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_SLIDE_UP_RIGHT, ANIM_NAME_PLAYER_SLIDE_UP_RIGHT, 0, 35, 0.02f, false);
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


		// Fire
		GameEngineInput::GetInst()->CreateKey(KEY_FIRE, VK_SPACE);

		// TODO::���� ���ÿ� ���� Ű ����, �����ʿ�
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_BAZ, '1');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_GRENADE, '2');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_AIRSTRIKE, '3');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_SHEEP, '4');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_SUPERSHEEP, '5');

		GameEngineInput::GetInst()->CreateKey(KEY_PLAYER_DEATH, 'G');
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
	if (false == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		return false;
	}

	return true;
}

bool Player::IsJumpKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		return false;
	}

	return true;
}

bool Player::IsBackFlipKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_MOVE_BACKFLIP))
	{
		return false;
	}

	return true;
}

bool Player::IsPlayerDeathKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(KEY_PLAYER_DEATH))
	{
		return false;
	}
	
	return true;
}

bool Player::IsBackFlipKeyFree()
{
	if (false == GameEngineInput::GetInst()->IsFree(KEY_MOVE_BACKFLIP))
	{
		return false;
	}

	return true;
}


// �׼�Ű�� ������ ���� ���
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_FIRE))
	{
		return false;
	}

	return true;
}

// �׼�Ű�� ������ ���
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_FIRE))
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

// �̵��� �浹üũ
void Player::MoveCheck(float4 _MoveDir)
{
	// MoveDir�� ���� �̵��߿����� ���ŵ�.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// TODO::�ø����� ���
	// GetMapColImage();
	float4 NextLeftPos = { GetPosition().x + CheckLength.x - PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - 5.0f};
	float4 NextRightPos = { GetPosition().x + CheckLength.x + PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - 5.0f };
	

	int LeftColor = ColMapImage_->GetImagePixel(NextLeftPos);
	int RightColor = ColMapImage_->GetImagePixel(NextRightPos);

	// TODO::�ʰ� �浹 ����

	CheckHillPixel();
	// �̵�

	if(RGB(0,0,255) != LeftColor &&
		RGB(0,0,255)!=RightColor)
	{

		SetMove(MoveDir_* GameEngineTime::GetDeltaTime()* Speed_);
	}

}

// ������ �浹üũ
void Player::MoveFall()
{
	float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

	float4 NextPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2  };
	int Color = ColMapImage_->GetImagePixel(NextPos);

	if (RGB(0, 0, 255) != Color)
	{		
		FallLength_ += FallSpeed_ * GameEngineTime::GetDeltaTime();
		FallSpeed_ += 50.0f * GameEngineTime::GetDeltaTime();

		// �ִ� ���ϼӵ�
		if (FallSpeed_ >= PLAYER_SPEED_FALL_MAX)
		{
			FallSpeed_ = PLAYER_SPEED_FALL_MAX;
		}

		SetMove(float4::DOWN* GameEngineTime::GetDeltaTime()* FallSpeed_);
	}
	else
	{
		if (FallLength_ >= 200.0f)
		{
			// ������ ó��
			//PlayerHp_ -= static_cast<int>(FallLength_ / 80.0f);
		}
		FallSpeed_ = PLAYER_SPEED_FALL;




		// TODO::���� ���¿� ���� �ٸ� ����ó��
		// X���� �����ϴ� ������ ��쿡�� �̲�����
		// X���� �������� �ʴ� ������ ��쿡�� ���� ����
	}


}

// �ʰ��� �浹üũ
void Player::CheckHillPixel()
{
	float4 LeftUpPos = float4::UP;
	float4 RightUpPos = float4::UP;

	int LeftUpColor = ColMapImage_->GetImagePixel(GetPosition() + float4{ -12.0f, 0.0f } + float4::DOWN * 7.0f);
	int RightUpColor = ColMapImage_->GetImagePixel(GetPosition() + float4{ 12.0f, 0.0f } + float4::DOWN * 7.0f);


	// TODO::�ʰ� �浹 ����

	if (RGB(0, 0, 255) == LeftUpColor)
	{
		SetMove(LeftUpPos);
	}
	else if (RGB(0, 0, 255) == RightUpColor)
	{
		SetMove(RightUpPos);
	}
}



// ���� ����
void Player::StateChange(PlayerState _State)
{
	Sound_BackflipOn = false;
	Sound_JumpOn = false;

	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::WeaponSwap:
			WeaponSwapStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Slide:
			SlideStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::BackFlip:
			BackFlipStart();
			break;
		case PlayerState::Falled:
			FalledStart();
			break;
		case PlayerState::Action:
			ActionStart();
			break;
		case PlayerState::FlyAway:
			FlyAwayStart();
			break;
		case PlayerState::Death:
			DeathStart();
			break;
		case PlayerState::None:
			CurrentState_ = _State;
			return;
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
	case PlayerState::WeaponSwap:
		WeaponSwapUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	case PlayerState::Slide:
		SlideUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::BackFlip:
		BackFlipUpdate();
		break;
	case PlayerState::Falled:
		FalledUpdate();
		break;
	case PlayerState::Action:
		ActionUpdate();
		break;
	case PlayerState::FlyAway:
		FlyAwayUpdate();
		break;
	case PlayerState::Death:
		DeathUpdate();
		break;
	case PlayerState::None:
		return;
	default:
		break;
	}

}

void Player::PlayerAnimationChange(std::string _Anim)
{

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		DirName_ = ANIM_KEYWORD_DIR_LEFT;
	}
	if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		DirName_ = ANIM_KEYWORD_DIR_RIGHT;
	}

	PlayerRenderer_->ChangeAnimation(_Anim + DirName_);
}

// ���� ���� ����
void Player::MoveWeaponAngle(float _DeltaTime)
{
	static float angleDiff = 0.0f;
	float DefaultAngle = 0.0f;
	float AllAddAngle = 0.0f;

	// �÷��̾ ������ ���� ���� ��� ������ �⺻���� ������ �ǵ���
	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		DefaultAngle = 180.0f;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_ANGLE_DOWN))
	{
		angleDiff += 120 * _DeltaTime;
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_ANGLE_UP))
	{
		angleDiff -= 120 * _DeltaTime;
	}

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		AllAddAngle = DefaultAngle - angleDiff;

		if (AllAddAngle >= 265.0f)
		{
			AllAddAngle = 265.0f;
			angleDiff = -85.0f;
		}
		else if (AllAddAngle <= 95.0f)
		{
			AllAddAngle = 95.0f;
			angleDiff = 85.0f;
		}

		ShotAngle_ = float4::DegreeToDirectionFloat4(AllAddAngle);
	}
	else
	{
		AllAddAngle = DefaultAngle + angleDiff;

		if (AllAddAngle >= 85.0f)
		{
			AllAddAngle = 85.0f;
			angleDiff = 85.0f;
		}
		else if (AllAddAngle <= -85.0f)
		{
			AllAddAngle = -85.0f;
			angleDiff = -85.0f;
		}

		ShotAngle_ = float4::DegreeToDirectionFloat4(AllAddAngle);
	}

	// ũ�ν���� : 3��° ���ڴ� ũ�ν���� Ȱ��ȭ ����
	Crshair_->UpdateCrosshairPos(GetPosition(), ShotAngle_);
}

// ���� �Ŀ� ����
void Player::ChargingWeaponPower()
{
	if (true == IsActionKeyPress())
	{
		ShotPower_ += 10.0f;
		CrgBlob_->SetChargePower(ShotPower_, GetPosition(), ShotAngle_);

		if (ShotPower_ >= WEAPON_MAX_SHOT_POWER)
		{
			ShotPower_ = WEAPON_MAX_SHOT_POWER;

			CrgBlob_->DeActivate();
			Crshair_->Off();

			// �ִ밪�� �Ѿ�� �ڵ����� �߻�ǵ���
			StateChange(PlayerState::Action);
		}
	}
}

void Player::ChangeHpBarFont(int _Hp)
{
	Hpbar_->ChangeHpBarFont(_Hp);
}

void Player::SetFontColor(FONT_COLOR _Color)
{
	if (Hpbar_ != nullptr)
	{
		Hpbar_->SetFontColor(_Color);
	}
}

void Player::CreateHpBar(int _Hp, float4 _Pivot, FONT_COLOR _Color)
{
	// HpBar
	Hpbar_ = GetLevel()->CreateActor<HpBar>();
	Hpbar_->SetFontColor(_Color);
	Hpbar_->ChangeHpBarFont(_Hp);

}

void Player::CreateControlArrow(TeamColor _TeamColor)
{
	ControlWorms_ = CreateRenderer();
	std::string Color;

	switch (_TeamColor)
	{
	case TeamColor::Red:
		Color = "ArrowRed.bmp";
		break;
	case TeamColor::Blue:
		Color = "ArrowBlue.bmp";
		break;
	case TeamColor::Green:
		Color = "arrowGreen.bmp";
		break;
	case TeamColor::Yellow:
		Color = "ArrowYellow.bmp";
		break;
	case TeamColor::Pink:
		Color = "arrowPink.bmp";
		break;
	case TeamColor::Mint:
		Color = "arrowMint.bmp";
		break;
	default:
		break;
	}

	ControlWorms_->CreateAnimation(Color,"ArrowUpdate", 0, 29, 0.04f, true);
	ControlWorms_->ChangeAnimation("ArrowUpdate");
	ControlWorms_->SetPivot({0, -90.f});
	ControlWorms_->SetOrder(static_cast<int>(RenderOrder::UI_2));
	ControlWorms_->Off();

}


void Player::Damaged(float4 _WeaponPos /*= float4::ZERO */)
{
	float4 Length = float4::ZERO;

	if (true == _WeaponPos.IsZero2D())
	{
		Length = GetPosition() - WeaponPos_;
	}
	else
	{
		Length = GetPosition() - _WeaponPos;
	}

	//�Ѿ˰� �÷��̾� ������ �Ÿ�
	Len_ = Length.Len2D();

	if (Len_ > 50.0f)
	{
		return;
	}

	//���󰡴� ���⸸ ���ϱ����� normalize 
	//����� FlyAway�Լ�����
	Length.Normal2D();


	/// IsDamaged_�� true�� �ɶ� IsDamagedCam_�� �Բ� true�� �ǵ��� �������ٰ�

	//50�� ���߹��� �ִ�Ÿ�
	//���ڶ��� ������ ��¦�и���.
	if (40.0f < Len_ && Len_ <= 50.0f)
	{

		IsDamaged_ = true;
		IsDamagedCam_ = true;
		FlySpeed_ = 20.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (30.0f < Len_ && Len_ <= 40.0f)
	{

		IsDamaged_ = true;
		IsDamagedCam_ = true;
		FlySpeed_ = 100.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (20.0f < Len_ && Len_ <= 30.0f)
	{

		IsDamaged_ = true;
		IsDamagedCam_ = true;
		FlySpeed_ = 200.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (10.0f < Len_ && Len_ <= 20.0f)
	{

		IsDamaged_ = true;
		IsDamagedCam_ = true;
		FlySpeed_ = 400.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (0.0f < Len_ && Len_ <= 10.0f)
	{
		IsDamaged_ = true;
		IsDamagedCam_ = true;
		FlySpeed_ = 600.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}


	//������� �Դµ��� IsDamaged�� false ��°� �����ʾҴٴ� ��.
	if (IsDamaged_ == false)
	{
		return;
	}

	//���������
	for (int Damage = 1; Damage <= 50; Damage++)
	{
		if (Damage == static_cast<int>(50 - Len_))
		{
			AllDamage_ += Damage;
			Damage_ += Damage;
			//PlayerHp_ -= Damage;
			////Hp�� 0���� ������ 0����
			//if (PlayerHp_ <= 0)
			//{
			//	PlayerHp_ = 0;
			//}
		}
	}

	//// HP UI�� ǥ�õ� HP����
	//Hpbar_->ChangeHpBarFont(PlayerHp_);
}


void Player::CheckDeath()
{
	if (GetPosition().y >= SCALE_MAPBOOKS_Y)
	{
		IsDeath_ = true;
	}


	if (PlayerHp_ == 0)
	{
		DeathDelayTime_ -= GameEngineTime::GetDeltaTime();
		if (DeathDelayTime_ <= 0)
		{
			StateChange(PlayerState::Death);
		}
	//	IsDeath_ = true;
	}


	if (IsDeath_ == false)
	{
		return;
	}

}