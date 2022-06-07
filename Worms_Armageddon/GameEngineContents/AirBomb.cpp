#include "AirBomb.h"
#include <GameEngine/GameEngineRenderer.h>

AirBomb::AirBomb() 
	:BombCount_(0)
{
	IsBounce_ = false;
}

AirBomb::~AirBomb() 
{
}

void AirBomb::Start()
{
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage(IMG_AIRJET_AIRBOMB_SPIN);
	WeaponRender_->SetRotationFilter(IMG_AIRJET_AIRBOMB_FILTER);
}

void AirBomb::Update()
{
	ThrowStart(0); // 투사체를 던지고
	BulletMove(100, false); // 그게 날아가서
	BulletColEvent(); // 충돌하면 이벤트가 발생한다.

	if (BombCount_ == 2)
	{
		WeaponCameraPos_ = GetPosition();
	}
}

bool AirBomb::WeaponUpdate()
{
	return false;
}