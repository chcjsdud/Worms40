#include "Baz.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Baz::Baz()
{
}

Baz::~Baz()
{
}

void Baz::Start()
{
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("BazSpin.bmp");
	WeaponRender_->SetRotationFilter("BazSpinFilter.bmp");
}
void Baz::Update()
{
	
}

bool Baz::WeaponUpdate()
{
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	ThrowStart(100); // 투사체를 던지고
	BulletMove(100); // 그게 날아가서
	BulletColEvent(); // 충돌하면 이벤트가 발생한다.

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}
