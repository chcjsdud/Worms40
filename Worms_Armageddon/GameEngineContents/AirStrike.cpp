#include "AirStrike.h"
#include "Cursor.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

AirStrike::AirStrike() 
	: IsBomb_(false)
	, IsAirOff_(true)
{
}

AirStrike::~AirStrike() 
{
}

void AirStrike::Start()
{
}

void AirStrike::Update()
{

}

bool AirStrike::WeaponUpdate()
{	
	if (true == IsBomb_)
	{
		if (IsAirOff_)
		{
			ReSetAccTime();
			IsAirOff_ = false;
		}
		
		if (1.f < GetAccTime())
		{
			Off();
		}
	}

	AirStart(float4::LEFT); // ���ݱ� ���
	// ���ݱⰡ ��θ� �� �������� ���� �� �Ѿ

	IsBomb_ = Bombing(WeaponState::AirStrike);
	

	if (false == WeaponStaticReturn_) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		WeaponCameraPos_ = float4::ZERO;
		WeaponStaticReturn_ = true;
		return false;
	}
	else
	{
		return true;
	}
}

float4 AirStrike::GetWeaponPosition()
{
	if (IsBomb_ == false || WeaponCameraPos_.IsZero2D())
	{
		return { GetPosition().x, GetPosition().y + 500 };
	}
	if (IsBomb_ == true)
	{
		return { WeaponCameraPos_.x,WeaponCameraPos_.y + 500 };
	}

	return GetPosition();
}