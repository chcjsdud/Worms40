#include "Grenade.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Grenade::Grenade() 
{
}

Grenade::~Grenade() 
{
}

void Grenade::Start()
{
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("GrenadeSpin.bmp");
	WeaponRender_->SetRotationFilter("GrenadeSpinFilter.bmp");
}
void Grenade::Update()
{

}

bool Grenade::WeaponUpdate()
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


	return true;
}