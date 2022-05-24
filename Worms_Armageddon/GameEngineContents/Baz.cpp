#include "Baz.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameENgine/GameEngine.h>

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
void Baz::Render()
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
}
