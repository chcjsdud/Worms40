#include "WeaponMaster.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>

GameMapMaster* WeaponMaster::GameMap_ = nullptr;

WeaponMaster::WeaponMaster() 
	: Shot_ (false)
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

bool WeaponMaster::BulletColEvent()
{
	int Color = GetGameMap()->GetColMap()->GetImagePixel({ GetPosition() });

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

		Off();
		return false;
	}

	// 동작
	//  동작
	//  동작
	//  동작
	// 동작 중
	return true;
}