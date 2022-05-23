#include "WeaponMaster.h"
#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineImage.h>

GameMapMaster* WeaponMaster::GameMap_ = nullptr;

WeaponMaster::WeaponMaster() 
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