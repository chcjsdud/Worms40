#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>

SuperSheep::SuperSheep() 
{
}

SuperSheep::~SuperSheep() 
{
}

void SuperSheep::Start()
{

}

void SuperSheep::Update()
{

}

bool SuperSheep::WeaponUpdate()
{
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}
