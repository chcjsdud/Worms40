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
	BulletDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * _Gravity; // �߷�
	BulletDir_ += WindInfo_ * GameEngineTime::GetDeltaTime(); // �ٶ�����

	float4 MyPos = GetPosition(); // ���� ��ġ
	float4 GetNextPos = BulletDir_ + GetPosition(); // �̷� ��ġ

	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BulletDir_);
	WeaponRender_->SetRotationZ(Degree + 90); // ���⿡ ���� ����ü ����
}

bool WeaponMaster::BulletColEvent()
{
	int Color = GetGameMap()->GetColMap()->GetImagePixel({ GetPosition() });

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

		Off();
		return false;
	}

	// ����
	//  ����
	//  ����
	//  ����
	// ���� ��
	return true;
}