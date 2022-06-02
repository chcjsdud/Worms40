#include "WeaponMaster.h"
#include "PlayLevel.h"
#include "Foom.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

GameMapMaster* WeaponMaster::GameMap_ = nullptr;

WeaponMaster::WeaponMaster() 
	: TargetPos_(float4::ZERO)
	, Shot_ (false)
	, WeaponRender_(nullptr)
	, IsBounce_(false)
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

void WeaponMaster::ThrowStart(float _ThrowForce)
{
	if (false == Shot_)
	{
		BulletDir_ += float4::UP * _ThrowForce;

		PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
		WindInfo_ = Play->GetWindDir();

		if (float4::LEFT.CompareInt2D(ShotDir_))
		{
			BulletDir_ += float4::LEFT * 100;
		}
		else
		{
			BulletDir_ += float4::RIGHT * 100;
		}
		Shot_ = true;
	}
}

void WeaponMaster::AirStart(float4 _FlyDir)
{
	if (false == Shot_)
	{
		PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
		if (nullptr == Play->GetCursor())
		{
			return;
		}

		Cursor* WeaponCusor = Play->GetCursor();
		//TargetPos_ = WeaponCusor->GetCursorPos(); // 커서 좌표 받음

		WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
		float AirHight = 300;
		float FlySpeed = 500;
		if (float4::LEFT.CompareInt2D(_FlyDir))
		{// ->
			WeaponRender_->SetImage(IMG_AIRJET_GREEN_RIGHT);
			SetPosition({ 300,AirHight });
			BulletDir_ = float4::RIGHT * FlySpeed;
		}
		else
		{// <-
			WeaponRender_->SetImage(IMG_AIRJET_GREEN_LEFT);
			SetPosition({ 300,AirHight });
			BulletDir_ = float4::LEFT * FlySpeed;
		}

		Shot_ = true;
	}
	else
	{
		SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
	}
}

void WeaponMaster::BulletMove(float _Gravity)
{
	SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
	BulletDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * _Gravity; // 중력
	BulletDir_ += WindInfo_ * GameEngineTime::GetDeltaTime(); // 바람영향

	float4 MyPos = GetPosition(); // 현재 위치
	float4 GetNextPos = BulletDir_ + GetPosition(); // 미래 위치

	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BulletDir_);
	WeaponRender_->SetRotationZ(Degree + 90); // 방향에 따른 투사체 각도
}

void WeaponMaster::BulletColEvent()
{
	int Color = GetGameMap()->GetColMap()->GetImagePixel({ GetPosition() });

	if (IsBounce_ == true)
	{
		BulletDir_ = PixelCol_->Bounce(GetPosition(), BAZ_COL_SIZE, GetGameMap()->GetColMap(), BulletDir_);

		// 튕겼으면 감속
		if (PixelCol_->GetBounceFlg() == true)
		{
			//BulletDir_ *= 0.8f;
		}

		// 너무 느려졌으면 속도를 0으로 설정
		if (BulletDir_.y < 1.0f && BulletDir_.y > -1.0f)
		{
			BulletDir_ *= float4{1.0f, 0.0f};
		}
	}
	else
	{
		// 맵과 충돌처리
		if (RGB(0, 0, 255) == Color)
		{
			// 이미지를 가져와서 땅이 파여있는 상태를 메모리에 보존?
			// 바닥
			GameEngineImage* tmpGroundMap = GetGameMap()->GetGround()->GetImage();
			// 충돌
			GameEngineImage* tmpColMap = GetGameMap()->GetColMap();
			GameEngineImage* tmpEffectImg = GameEngineImageManager::GetInst()->Find(IMG_EFFECT_BOOM);

			// {0, 255, 0}의 원이 그려진 tmpGoundMap를 메인버퍼에 transCopy
			// tmpGoundMap에 {0, 255, 0}의 원 그리기처리
			tmpGroundMap->TransCopy(tmpEffectImg, // _Other
				{ GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
				tmpEffectImg->GetScale(), // _CopyScale
				{ 0, 0 }, // _OtherPivot
				tmpEffectImg->GetScale(), // _OtherScale
				RGB(0, 255, 0) // TransColor
			);

			// tmpColMap에 {0, 255, 0}의 원 그리기처리
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