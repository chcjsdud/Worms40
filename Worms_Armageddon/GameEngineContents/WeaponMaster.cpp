#include "WeaponMaster.h"
#include "PlayLevel.h"
#include "Foom.h"
#include "PixelCollision.h"
#include "AirBomb.h"
#include "Player.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

GameMapMaster* WeaponMaster::GameMap_ = nullptr;
float4 WeaponMaster::WeaponCameraPos_ = float4::ZERO;
bool WeaponMaster::WeaponStaticReturn_ = true;
GameEngineActor* WeaponMaster::AirBombArr_[5] = { nullptr };
GameEngineActor* WeaponMaster::ExplodeWeapon_ = nullptr;

WeaponMaster::WeaponMaster() 
	: TargetPos_(float4::ZERO)
	, IsShot_ (false)
	, IsDrop_(true) // �ʱ�ȭ�� ���� ���Ƿ� true
	, BombCnt_(0)
	, BounceRotate_(0)
	, IsBomb_(false)
	, IsExplodEnd_(false)
	, JumpTime_(0)
	, AnimalMoveDir_(float4::ZERO)
	, Speed_(100)
	, FallLength_(0)
	, FallSpeed_(0)
	, IsJump_(false)
	, IsJumpCol_(false)
	, JumpSpeed_(0)
	, JumpMoveDir_(float4::ZERO)
	, WindDirInfo_(float4::ZERO)
	, WeaponRender_(nullptr)
	, IsBounce_(false)
	, ShotDir_(float4::ZERO)
	, PixelCol_(nullptr)
	, BulletDir_(float4::ZERO)
	, ShotAngle_(float4::ZERO)
	, ShotPower_(0)
	, SelfDestructSec_(0)
	, TimerBox_(nullptr)
	, IsTimerCreate_(false)
{
}

WeaponMaster::~WeaponMaster() 
{
}


void WeaponMaster::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), static_cast<int>(5.f));
}

void WeaponMaster::Start()
{
	
}

void WeaponMaster::Update()
{
	
}

void WeaponMaster::Drop(WeaponState _Drop, float _Sec /*= 0*/)
{
	if (true == IsDrop_) // ���� �ð� ���� �ʱ�ȭ
	{
		ReSetAccTime();
		IsDrop_ = false;
	}

	switch (_Drop) // ���� ����
	{
	case WeaponState::AirStrike:
	{
		if (false == IsDrop_)
		{
			if (_Sec < GetAccTime())
			{
				float4 BombDir = float4::ZERO;
				BombDir.x = BulletDir_.x / WEAPON_AIRFLY_SPEED;

				AirBomb* Bomb = GetLevel()->CreateActor<AirBomb>();
				Bomb->SetPosition(GetPosition());
				Bomb->SetShotAngle(BombDir); // ���ݱⰡ ���ư��� �������� ��ô
				Bomb->SetBombCount(BombCnt_);
				Bomb->ResgistBomb();
				++BombCnt_;
				IsDrop_ = true;
			}
		}
	}
		break;
	default:
		break;
	}
}

void WeaponMaster::AnimalMoveCheck(float4 _Dir)
{
	// MoveDir�� ���� �̵��߿����� ���ŵ�.
	AnimalMoveDir_ = _Dir;
	float4 CheckLength = AnimalMoveDir_ * GameEngineTime::GetDeltaTime() * Speed_;

	// TODO::�ø����� ���
	// GetMapColImage();
	float NextYValue = 5.0f;
	float4 NextLeftPos = { GetPosition().x + CheckLength.x - PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - NextYValue };
	float4 NextRightPos = { GetPosition().x + CheckLength.x + PLAYER_SIZE_X / 2 , GetPosition().y + CheckLength.y - NextYValue };


	int LeftColor = GetGameMap()->GetColMap()->GetImagePixel(NextLeftPos);
	int RightColor = GetGameMap()->GetColMap()->GetImagePixel(NextRightPos);

	// TODO::�ʰ� �浹 ����

	{ // Hill Climb
		float UpValue = 1.0f;
		float4 LeftUpPos = float4::UP * UpValue;
		float4 RightUpPos = float4::UP * UpValue;

		int LeftUpColor = GetGameMap()->GetColMap()->GetImagePixel(GetPosition() + float4{ -12.0f, 0.0f } + float4::DOWN * 7.0f);
		int RightUpColor = GetGameMap()->GetColMap()->GetImagePixel(GetPosition() + float4{ 12.0f, 0.0f } + float4::DOWN * 7.0f);

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

	// �̵�
	if (RGB(0, 0, 255) != LeftColor &&
		RGB(0, 0, 255) != RightColor)
	{
		SetMove(AnimalMoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
}

void WeaponMaster::AnimalFall()
{
	float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;

	float4 NextPos = { GetPosition().x + CheckLength.x , GetPosition().y + CheckLength.y + PLAYER_SIZE_Y / 2 };
	int Color = GetGameMap()->GetColMap()->GetImagePixel(NextPos);

	if (RGB(0, 0, 255) != Color)
	{
		FallLength_ += FallSpeed_ * GameEngineTime::GetDeltaTime();
		FallSpeed_ += 50.0f * GameEngineTime::GetDeltaTime();

		// �ִ� ���ϼӵ�
		if (FallSpeed_ >= PLAYER_SPEED_FALL_MAX)
		{
			FallSpeed_ = PLAYER_SPEED_FALL_MAX;
		}

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_);
	}
	else
	{
		FallSpeed_ = PLAYER_SPEED_FALL;
		IsJump_ = false;
	}
}

void WeaponMaster::AnimalJump()
{
	if (IsJumpCol_ == false)
	{
		

		if (1.f < JumpTime_)
		{
			SoundPlayer_Explode_ = GameEngineSound::SoundPlayControl("SHEEPBAA.wav");
			SoundPlayer_Explode_.Volume(SND_VOL_BAZEXPLODE);
			JumpTime_ = 0;
		}

		IsJumpCol_ = true;
		//�浹�ϱ� �������� ���������ϴ� �������� ��,�� �̵�
		if (1 == AnimalMoveDir_.x)
		{
			JumpMoveDir_ = float4::RIGHT * (JumpSpeed_ - 100.0f);
		}
		else
		{
			JumpMoveDir_ = float4::LEFT * (JumpSpeed_ - 100.0f);
		}

		JumpMoveDir_ += float4::UP * JumpSpeed_;

		
	}

	if (IsJumpCol_ == true)
	{
		//�浹�� �� ,�� ����
		JumpMoveDir_ = PixelCol_->PlayerBounce(GetPosition(), { PLAYER_SIZE_X,PLAYER_SIZE_Y }, GetGameMap()->GetColMap(), JumpMoveDir_, JumpSpeed_);

		SetMove(JumpMoveDir_ * GameEngineTime::GetDeltaTime());

		JumpMoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * FallSpeed_;
		FallSpeed_ += 20.0f;

		//���� �غκ��ȼ� üũ�� ���� ����
		float4 LeftPosRight = float4::LEFT;
		float4 RightPosLeft = float4::RIGHT;
		float4 LeftPos = { GetPosition().x - PLAYER_SIZE_X, GetPosition().y };
		int LeftColor = GetGameMap()->GetColMap()->GetImagePixel(LeftPos);
		float4 RightPos = { GetPosition().x + PLAYER_SIZE_X, GetPosition().y };
		int RightColor = GetGameMap()->GetColMap()->GetImagePixel(RightPos);

		float4 CheckLength = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;
		float4 UpPos = float4::UP;
		float4 DownPos = { GetPosition().x, GetPosition().y + PLAYER_SIZE_Y / 2 };
		int DownColor = GetGameMap()->GetColMap()->GetImagePixel(DownPos);

		//������ �غκ��� �Ķ����̸�
		if (RGB(0, 0, 255) == DownColor)
		{
			JumpMoveDir_ = float4::ZERO;
			IsJump_ = false;
		}
	}
}

void WeaponMaster::ThrowStart(float _ThrowForce)
{
	if (false == IsShot_)
	{
		BulletDir_ += ShotAngle_ * _ThrowForce;
		AnimalMoveDir_ = ShotDir_; // ���� �̵��� ���� ����

		PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
		WindDirInfo_ = Play->GetWindDir(); // �ٶ� ���� ����

		IsShot_ = true;
	}
}

void WeaponMaster::AirStart(float4 _AirSpawn)
{
	if (false == IsShot_)
	{
		PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
		if (nullptr == Play->GetCursor())
		{
			return;
		}

		TargetCursor();
		
		WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
		if (float4::LEFT.CompareInt2D(_AirSpawn))
		{// ->
			WeaponRender_->SetImage(IMG_AIRJET_GREEN_RIGHT);
			SetPosition({ WEAPON_AIRFLY_START_LEFT,WEAPON_AIRFLY_HIGHT });
			BulletDir_ = float4::RIGHT * WEAPON_AIRFLY_SPEED;
		}
		else
		{// <-
			WeaponRender_->SetImage(IMG_AIRJET_GREEN_LEFT);
			SetPosition({ WEAPON_AIRFLY_START_RIGHT,WEAPON_AIRFLY_HIGHT });
			BulletDir_ = float4::LEFT * WEAPON_AIRFLY_SPEED;
		}

		SoundPlayer_Explode_ = GameEngineSound::SoundPlayControl("Airstrike.wav");
		SoundPlayer_Explode_.Volume(SND_VOL_BAZEXPLODE);

		IsShot_ = true;
	}
	else
	{
		SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
		
		if (WEAPON_AIRFLY_START_LEFT > GetPosition().x || // �� �̻� �̵��ϸ� ���ݱ� ������
			WEAPON_AIRFLY_START_RIGHT < GetPosition().x)
		{
			Off();
		}
	}
}

void WeaponMaster::TargetCursor()
{
	float4 CameraPos = GetLevel()->GetCameraPos();

	float4 CursorPos = Cursor::GetCursorPosition(); // ī�޶���ǥ���� Ŀ�� ��ġ ����

	TargetPos_ = CameraPos + CursorPos; // Ŀ���� ������ ������ǥ
}

void WeaponMaster::BulletMove(float _Gravity, bool _IsWind)
{
	SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
	BulletDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * _Gravity; // �߷�

	if (true == _IsWind)
	{
		BulletDir_ += WindDirInfo_ * GameEngineTime::GetDeltaTime(); // �ٶ�����
	}

	float4 MyPos = GetPosition(); // ���� ��ġ
	float4 GetNextPos = BulletDir_ + GetPosition(); // �̷� ��ġ

	if (true == IsBounce_)
	{
		WeaponRender_->SetRotationZ(BounceRotate_);
		if (MyPos.x < GetNextPos.x) // ->
		{
			BounceRotate_ += 5.f * BulletDir_.x * GameEngineTime::GetDeltaTime();
		}
		else if (MyPos.x > GetNextPos.x) // <-
		{
			BounceRotate_ += 5.f * BulletDir_.x * GameEngineTime::GetDeltaTime();
		}

		return;
	}

	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BulletDir_);
	WeaponRender_->SetRotationZ(Degree + 90); // ���⿡ ���� ����ü ����
}

bool WeaponMaster::Bombing(WeaponState _Bomb)
{
	if (0 < BulletDir_.x)
	{// ->
		float BombingStartPosX = TargetPos_.x - CorrectionPosX;

		if (BombingStartPosX < GetPosition().x) // ���� ��ġ����
		{
			switch (BombCnt_)
			{
			case 0:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 1:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 2:
			{
				Drop(_Bomb, DropSec);
				IsBomb_ = true;
			}
			break;
			case 3:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 4:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			default:
				break;
			}
		}
	}
	else
	{// <-
		float BombingStartPosX = TargetPos_.x + CorrectionPosX;

		if (BombingStartPosX > GetPosition().x) // ���� ��ġ����
		{
			switch (BombCnt_)
			{
			case 0:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 1:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 2:
			{
				Drop(_Bomb, DropSec);
				IsBomb_ = true;
			}
			break;
			case 3:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			case 4:
			{
				Drop(_Bomb, DropSec);
			}
			break;
			default:
				break;
			}
		}
	}

	return IsBomb_;
}

void WeaponMaster::AnimalMove(WeaponState _Animal)
{
	JumpTime_ += GameEngineTime::GetDeltaTime();
	if (false == IsJump_)
	{
		AnimalMoveCheck(ShotDir_);

		if (false == IsJump_)
		{
			JumpSpeed_ = 200.0f;
			IsJumpCol_ = false;
			PixelCol_->SetBounceFlgFalse();
			JumpMoveDir_ = float4::ZERO;
			IsJump_ = true;
		}

		AnimalFall(); 
	}
	else
	{
		AnimalJump();
	}
}

bool WeaponMaster::BulletColEvent()
{
	int Color = GetGameMap()->GetColMap()->GetImagePixel({ GetPosition() });

	if (IsBounce_ == true)
	{
		BulletDir_ = PixelCol_->Bounce(GetPosition(), BAZ_COL_SIZE, GetGameMap()->GetColMap(), BulletDir_);

		// ƨ������ ����
		if (PixelCol_->GetBounceFlg() == true)
		{
			BulletDir_ *= 0.5f;
		}

		// �ʹ� ���������� �ӵ��� 0���� ����
		if (BulletDir_.y < 1.0f && BulletDir_.y > -1.0f)
		{
			BulletDir_ *= float4{1.0f, 0.0f};
		}
	}
	else
	{
		// �ʰ� �浹ó��
		if (RGB(0, 0, 255) == Color)
		{
			// ���� ���� ����Ʈ
			Explosion();
			IsExplodEnd_ = true;
			// ���Ⱑ ���������� ��ȯ(������ ó����)
			return false;
		}
	}
	IsExplodEnd_ = false;
	return true;
}

void WeaponMaster::Explosion()
{
	// ������
	//GameEngineSound::SoundPlayOneShot("rocketrelease.wav", 0);
	SoundPlayer_Explode_ = GameEngineSound::SoundPlayControl("rocketrelease.wav");
	SoundPlayer_Explode_.Volume(SND_VOL_BAZEXPLODE);

	IsExplodEnd_ = true;
	// �̹����� �����ͼ� ���� �Ŀ��ִ� ���¸� �޸𸮿� ����?
	// �ٴ�
	GameEngineImage* tmpGroundMap = GetGameMap()->GetGround()->GetImage();
	// �浹
	GameEngineImage* tmpColMap = GetGameMap()->GetColMap();
	GameEngineImage* tmpEffectImg = GameEngineImageManager::GetInst()->Find(IMG_EFFECT_BOOM);

	// {0, 255, 0}�� ���� �׷��� tmpGoundMap�� ���ι��ۿ� transCopy
	// tmpGoundMap�� {0, 255, 0}�� �� �׸���ó��
	tmpGroundMap->TransCopy(tmpEffectImg, // _Other
		{ GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
		tmpEffectImg->GetScale(), // _CopyScale
		{ 0, 0 }, // _OtherPivot
		tmpEffectImg->GetScale(), // _OtherScale
		RGB(0, 255, 0) // TransColor
	);

	// tmpColMap�� {0, 255, 0}�� �� �׸���ó��
	tmpColMap->TransCopy(tmpEffectImg, // _Other
		{ GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
		tmpEffectImg->GetScale(), // _CopyScale
		{ 0, 0 }, // _OtherPivot
		tmpEffectImg->GetScale(), // _OtherScale
		RGB(0, 255, 0) // TransColor
	);
	EffectManager* Effect = GetLevel()->CreateActor<Foom>();
	Effect->SetPosition(GetPosition());

	ExplodeWeapon_ = this;
	Off();
}

bool WeaponMaster::IsBulletOutofBound()
{
	if (GetPosition().y >= SCALE_MAPBOOKS_GROUND_Y)
	{
		return true;
	}

	return false;
}
