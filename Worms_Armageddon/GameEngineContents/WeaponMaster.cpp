#include "WeaponMaster.h"
#include "PlayLevel.h"
#include "Foom.h"
#include "PixelCollision.h"
#include "AirBomb.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

GameMapMaster* WeaponMaster::GameMap_ = nullptr;
float4 WeaponMaster::WeaponCameraPos_ = float4::ZERO;

WeaponMaster::WeaponMaster() 
	: TargetPos_(float4::ZERO)
	, IsShot_ (false)
	, IsDrop_(true) // �ʱ�ȭ�� ���� ���Ƿ� true
	, WeaponRender_(nullptr)
	, IsBounce_(false)
	, BounceRotate_(0)
	, IsBomb_(false)
	, BombCnt_(0)
{
}

WeaponMaster::~WeaponMaster() 
{
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
				AirBomb* Bomb = GetLevel()->CreateActor<AirBomb>();
				Bomb->SetPosition(GetPosition());
				Bomb->SetBombCount(BombCnt_);
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

void WeaponMaster::ThrowStart(float _ThrowForce)
{
	if (false == IsShot_)
	{
		BulletDir_ += float4::UP * _ThrowForce;

		PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
		WindInfo_ = Play->GetWindDir(); // �ٶ� ���� ����

		if (float4::LEFT.CompareInt2D(ShotDir_))
		{
			BulletDir_ += float4::LEFT * 100;
		}
		else
		{
			BulletDir_ += float4::RIGHT * 100;
		}
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

		Cursor* WeaponCusor = Play->GetCursor();
		TargetPos_ = WeaponCusor->GetMouseCursorPos(); // Ŀ�� ��ǥ ����

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

void WeaponMaster::BulletMove(float _Gravity, bool _IsWind)
{
	SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
	BulletDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * _Gravity; // �߷�

	if (true == _IsWind)
	{
		BulletDir_ += WindInfo_ * GameEngineTime::GetDeltaTime(); // �ٶ�����
	}

	float4 MyPos = GetPosition(); // ���� ��ġ
	float4 GetNextPos = BulletDir_ + GetPosition(); // �̷� ��ġ

	if (true == IsBounce_)
	{
		WeaponRender_->SetRotationZ(BounceRotate_);
		if (MyPos.x < GetNextPos.x) // ->
		{
			BounceRotate_ += 0.1f * BulletDir_.x;
		}
		else if (MyPos.x > GetNextPos.x) // <-
		{
			BounceRotate_ += 0.1f * BulletDir_.x;
		}

		return;
	}

	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BulletDir_);
	WeaponRender_->SetRotationZ(Degree + 90); // ���⿡ ���� ����ü ����
}

bool WeaponMaster::Bombing(WeaponState _Bomb)
{
	float DropSec = 0.05f;

	if (0 < BulletDir_.x)
	{// ->
		float BombingStartPosX = TargetPos_.x -300;

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
		float BombingStartPosX = TargetPos_.x - 300;

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

void WeaponMaster::BulletColEvent()
{
	int Color = GetGameMap()->GetColMap()->GetImagePixel({ GetPosition() });

	if (IsBounce_ == true)
	{
		BulletDir_ = PixelCol_->Bounce(GetPosition(), BAZ_COL_SIZE, GetGameMap()->GetColMap(), BulletDir_);

		// ƨ������ ����
		if (PixelCol_->GetBounceFlg() == true)
		{
			BulletDir_ *= 0.8f;
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

			Off();
		}
	}

}