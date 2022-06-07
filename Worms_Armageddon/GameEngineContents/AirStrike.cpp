#include "AirStrike.h"
#include "Cursor.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

AirStrike::AirStrike() 
	: IsBomb_(false)
{
}

AirStrike::~AirStrike() 
{
}

void AirStrike::Start()
{
	IsBounce_ = false;
}

void AirStrike::Update()
{

}

bool AirStrike::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}
	
	AirStart(float4::RIGHT); // ���ݱ� ���
	// ���ݱⰡ ��θ� �� �������� ���� �� �Ѿ

	IsBomb_ = Bombing(WeaponState::AirStrike);
	

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		WeaponCameraPos_ = float4::ZERO;
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
		return GetPosition();
	}
	if (IsBomb_ == true)
	{
		return WeaponCameraPos_;
	}

	return GetPosition();
}