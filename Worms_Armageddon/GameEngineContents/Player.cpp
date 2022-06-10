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
	, FlySpeed_(0.0f)

{
}

Player::~Player()
{
}

void Player::Start()
{
	//임시 DirName 초기값
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

	// 테스트 임시 데이터
	ColMapImage_ = GameEngineImageManager::GetInst()->Find(IMG_MAPBOOKS_GROUND);


}

void Player::Update()
{
	//데미지를 입엇다면 , IsDamged==true , Damaged함수에서 처리.
	if (IsDamaged_ == true)
	{
		FlyAwayUpdate();
		return;
	}

	// 컨트롤되고 있지 않은 플레이어 캐릭터는 피격판정등의 동작만 수행
	if (this->GetPlayerState() == PlayerState::Idle
		|| this->GetPlayerState() == PlayerState::Move)
	{
		MoveFall();
	}

	Hpbar_->HpBarSetPosition(this->GetPosition());

	//Weapon이 생성되고 땅에닿아 폭발했다면
	if (Weapon_ != nullptr && Weapon_->GetExplodEndFlg() == true)
	{
		Damaged();

		if (IsDamaged_ == true)
		{
			FlyAwayStart();
		}
	}


	// 컨트롤되고 있지 않은 캐릭터는 데미지를 받더라도 턴이 끝나지 않음
}

void Player::Render()
{	
}

bool Player::ControllUpdate()
{
	// State내부에서 턴종료 플래그를 세워주면 턴종료
	IsTurnEnd_ = false;

	if (IsDamaged_ == true)
	{
		return IsTurnEnd_;
	}

	StateUpdate();


	return IsTurnEnd_;
}


bool Player::DeathUpdate()
{
	if (true /* WeaponDeath */)
	{
		// TODO::죽음 처리가 끝나면 true리턴
		return true;
	}

	return false;
}

void Player::PlayerAnimationInit()
{
	PlayerRenderer_ = CreateRenderer((int)RenderOrder::Player);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_RIGHT, ANIM_NAME_PLAYER_IDLE_RIGHT, 0, 5, 0.1f, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_IDLE_LEFT, ANIM_NAME_PLAYER_IDLE_LEFT, 0, 5, 0.1f, true);

	// 웨폰 애니메이션
	//바주카
	PlayerRenderer_->CreateAnimation(IMG_BAZ_ON_LEFT, ANIM_NAME_BAZ_ON_LEFT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_ON_RIGHT, ANIM_NAME_BAZ_ON_RIGHT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_OFF_LEFT, ANIM_NAME_BAZ_OFF_LEFT, 0, 5, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_BAZ_OFF_RIGHT, ANIM_NAME_BAZ_OFF_RIGHT, 0, 5, 0.03f, false);

	//수류탄
	PlayerRenderer_->CreateAnimation(IMG_GRN_ON_LEFT, ANIM_NAME_GRN_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_ON_RIGHT, ANIM_NAME_GRN_ON_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_OFF_LEFT, ANIM_NAME_GRN_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_GRN_OFF_RIGHT, ANIM_NAME_GRN_OFF_RIGHT, 0, 9, 0.03f, false);

	//에어스트라이크
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_OFF_LEFT, ANIM_NAME_AIRSTRIKE_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_ON_LEFT, ANIM_NAME_AIRSTRIKE_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_OFF_RIGHT, ANIM_NAME_AIRSTRIKE_OFF_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_AIRSTRIKE_ON_RIGHT, ANIM_NAME_AIRSTRIKE_ON_RIGHT, 0, 9, 0.03f, false);
	//양폭탄
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_OFF_LEFT, ANIM_NAME_SHEEP_OFF_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_ON_LEFT, ANIM_NAME_SHEEP_ON_LEFT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_OFF_RIGHT, ANIM_NAME_SHEEP_OFF_RIGHT, 0, 9, 0.03f, false);
	PlayerRenderer_->CreateAnimation(IMG_SHEEP_ON_RIGHT, ANIM_NAME_SHEEP_ON_RIGHT, 0, 9, 0.03f, false);

	// 좌우 걷는 애니메이션
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WALK_LEFT, ANIM_NAME_PLAYER_WALKLEFT, 0, 14, 0.03f, true);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_WALK_RIGHT, ANIM_NAME_PLAYER_WALKRIGHT, 0, 14, 0.03f, true);

	//점프 전 준비동작 애니메이션
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_JUMPRDY_LEFT, ANIM_NAME_PLAYER_JUMPRDY_LEFT, 0, 9, 0.05f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_JUMPRDY_RIGHT, ANIM_NAME_PLAYER_JUMPRDY_RIGHT, 0, 9, 0.05f, false);

	//점프 애니메이션
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FLYLINK_LEFT, ANIM_NAME_PLAYER_JUMPLEFT, 0, 6, 0.1f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FLYLINK_RIGHT, ANIM_NAME_PLAYER_JUMPRIGHT, 0, 6, 0.1f, false);

	//백플립 애니메이션
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BACKFLIP_LEFT, ANIM_NAME_PLAYER_BACKFLIP_LEFT, 0, 21, 0.02f, false);
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_BACKFLIP_RIGHT, ANIM_NAME_PLAYER_BACKFLIP_RIGHT, 0, 21, 0.02f, false);

	//낙하 애니메이션
	//33번째 이미지때 올라가게
	PlayerRenderer_->CreateAnimation(IMG_PLAYER_FALL, ANIM_NAME_PLAYER_FALL, 0, 48, 0.05, false);

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


		// Fire
		GameEngineInput::GetInst()->CreateKey(KEY_FIRE, VK_SPACE);

		// TODO::무기 선택용 더미 키 설정, 수정필요
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_BAZ, '1');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_GRENADE, '2');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_AIRSTRIKE, '3');
		GameEngineInput::GetInst()->CreateKey(KEY_WEAPON_SUPERSHEEP, '4');
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

bool Player::IsBackFlipKeyFree()
{
	if (false == GameEngineInput::GetInst()->IsFree(KEY_MOVE_BACKFLIP))
	{
		return false;
	}

	return true;
}


// 액션키가 눌리고 있을 경우
bool Player::IsActionKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(KEY_FIRE))
	{
		return false;
	}

	return true;
}

// 액션키가 떨어진 경우
bool Player::IsActionKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(KEY_FIRE))
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

// 이동중 충돌체크
void Player::MoveCheck(float4 _MoveDir)
{
	// MoveDir은 오직 이동중에서만 갱신됨.
	MoveDir_ = _MoveDir;
	float4 CheckLength = MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// TODO::컬리전맵 취득
	// GetMapColImage();
	float4 NextLeftPos = { GetPosition().x + CheckLength.x - PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - 5.0f};
	float4 NextRightPos = { GetPosition().x + CheckLength.x + PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - 5.0f };
	

	int LeftColor = ColMapImage_->GetImagePixel(NextLeftPos);
	int RightColor = ColMapImage_->GetImagePixel(NextRightPos);

	// TODO::맵과 충돌 판정

	CheckHillPixel();
	// 이동

	if(RGB(0,0,255) != LeftColor &&
		RGB(0,0,255)!=RightColor)
	{

		SetMove(MoveDir_* GameEngineTime::GetDeltaTime()* Speed_);
	}

}

// 낙하중 충돌체크
void Player::MoveFall()
{
	float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

	float4 NextPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2  };
	int Color = ColMapImage_->GetImagePixel(NextPos);

	if (RGB(0, 0, 255) != Color)
	{		
		FallLength_ += FallSpeed_ * GameEngineTime::GetDeltaTime();
		FallSpeed_ += 50.0f * GameEngineTime::GetDeltaTime();

		// 최대 낙하속도
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
			// 데미지 처리
			PlayerHp_ -= static_cast<int>(FallLength_ / 80.0f);
		}
		FallSpeed_ = PLAYER_SPEED_FALL;




		// TODO::낙하 상태에 따라서 다른 낙하처리
		// X값이 존재하는 낙하의 경우에는 미끄러짐
		// X값이 존재하지 않는 낙하의 경우에는 땅에 박힘
	}


}

// 맵과의 충돌체크
void Player::CheckHillPixel()
{
	float4 LeftUpPos = float4::UP;
	float4 RightUpPos = float4::UP;

	int LeftUpColor = ColMapImage_->GetImagePixel(GetPosition() + float4{ -12.0f, 0.0f } + float4::DOWN * 7.0f);
	int RightUpColor = ColMapImage_->GetImagePixel(GetPosition() + float4{ 12.0f, 0.0f } + float4::DOWN * 7.0f);


	// TODO::맵과 충돌 판정

	if (RGB(0, 0, 255) == LeftUpColor)
	{
		SetMove(LeftUpPos);
	}
	else if (RGB(0, 0, 255) == RightUpColor)
	{
		SetMove(RightUpPos);
	}
}



// 상태 변경
void Player::StateChange(PlayerState _State)
{
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
	case PlayerState::WeaponSwap:
		WeaponSwapUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
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
	default:
		break;
	}

}

void Player::UnControlStateChange(PlayerUnControlState _State)
{
	if (UnControlState_ != _State)
	{
		switch (_State)
		{
		case PlayerUnControlState::UncontrolIdle:
			UncontrolledStart();
			break;
		case PlayerUnControlState::FlyAway:
			FlyAwayStart();
			break;
		default:
			break;
		}
	}

	UnControlState_ = _State;
}

void Player::UnControlStateUpdate()
{
	switch (UnControlState_)
	{
	case PlayerUnControlState::UncontrolIdle:
		UncontrolledUpdate();
		break;
	case PlayerUnControlState::FlyAway:
		FlyAwayUpdate();
		break;
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

// 무기 각도 조절
void Player::MoveWeaponAngle()
{
	if (true == GameEngineInput::GetInst()->IsPress(KEY_ANGLE_DOWN))
	{
		ShotAngle_.y += 2.0f * GameEngineTime::GetDeltaTime();

		if (ShotAngle_.y >= ShotAngleMin_.y)
		{
			ShotAngle_.y = ShotAngleMin_.y;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_ANGLE_UP))
	{
		ShotAngle_.y -= 2.0f * GameEngineTime::GetDeltaTime();

		if (ShotAngle_.y <= ShotAngleMax_.y)
		{
			ShotAngle_.y = ShotAngleMax_.y;
		}
	}
}

// 무기 파워 조절
void Player::ChargingWeaponPower()
{
	if (true == IsActionKeyPress())
	{
		ShotPower_ += 10.0f;

		if (ShotPower_ >= WEAPON_MAX_SHOT_POWER)
		{
			ShotPower_ = WEAPON_MAX_SHOT_POWER;

			// 최대값을 넘어가면 자동으로 발사되도록
			StateChange(PlayerState::Action);
		}
	}
}

void Player::ChangeHpBarFont(int _Hp)
{
	Hpbar_->ChangeHpBarFont(_Hp, {0,0});
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
	Hpbar_->ChangeHpBarFont(_Hp, _Pivot);

}


void Player::Damaged()
{
	float4 Length = GetPosition() - Weapon_->GetWeaponPosition();
	//총알과 플레이어 사이의 거리
	Len_ = Length.Len2D();

	if (Len_ > 50.0f)
	{
		return;
	}

	//날라가는 방향만 구하기위해 normalize 
	//계산은 FlyAway함수에서
	Length.Normal2D();


	//50이 폭발범위 최대거리
	//끝자락에 맞으면 살짝밀린다.
	if (40.0f < Len_ && Len_ <= 50.0f)
	{

		IsDamaged_ = true;
		FlySpeed_ = 20.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (30.0f < Len_ && Len_ <= 40.0f)
	{

		IsDamaged_ = true;
		FlySpeed_ = 100.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (20.0f < Len_ && Len_ <= 30.0f)
	{

		IsDamaged_ = true;
		FlySpeed_ = 200.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (10.0f < Len_ && Len_ <= 20.0f)
	{

		IsDamaged_ = true;
		FlySpeed_ = 400.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}
	else if (0.0f < Len_ && Len_ <= 10.0f)
	{
		IsDamaged_ = true;
		FlySpeed_ = 600.0f;
		FlyMoveDir_ = Length * FlySpeed_;
	}


	//여기까지 왔는데도 IsDamaged가 false 라는건 맞지않았다는 뜻.
	if (IsDamaged_ == false)
	{
		return;
	}

	//데미지계산
	for (int Damage = 1; Damage <= 50; Damage++)
	{
		if (Damage == static_cast<int>(50 - Len_))
		{
			PlayerHp_ -= Damage;
			AllDamage_ += Damage;
		}
	}


}