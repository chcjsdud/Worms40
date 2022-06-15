#include "Baz.h"
#include "Enums.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngineBase/GameEngineSound.h>

Baz::Baz()
{
}

Baz::~Baz()
{
}

void Baz::Start()
{
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("BazSpin.bmp");
	WeaponRender_->SetRotationFilter("BazSpinFilter.bmp");
}
void Baz::Update()
{
	
}

bool Baz::WeaponUpdate()
{
	if (true == WeaponMaster::IsBulletOutofBound()) // 바다에 빠지면
	{
		Off();
		return false;
	}

	ThrowStart(ShotPower_); // 투사체를 던지고
	BulletMove(500, true); // 그게 날아가서
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
