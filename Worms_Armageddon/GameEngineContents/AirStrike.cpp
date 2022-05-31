#include "AirStrike.h"
#include "Cursor.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

AirStrike::AirStrike() 
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
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE)) // L
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}
	
	AirStart(float4::LEFT); // 폭격기 출격

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}