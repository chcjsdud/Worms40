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
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}
	
	AirStart(float4::RIGHT); // 폭격기 출격
	// 폭격기가 경로를 다 지나가야 다음 턴 넘어감

	IsBomb_ = Bombing(WeaponState::AirStrike);
	

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
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