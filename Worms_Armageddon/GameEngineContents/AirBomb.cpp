#include "AirBomb.h"
#include <GameEngine/GameEngineRenderer.h>
#include <string>

AirBomb::AirBomb() 
	:BombCount_(0)
{
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
	bool IsExplosion = true;
	

	if (true == WeaponMaster::IsBulletOutofBound())
	{
		AirBombExplodEnd_ = !IsExplosion;
		this->Death();
		WeaponMaster::AirBombArr_[BombCount_] = nullptr;

		if (BombCount_ == 2)
		{
			WeaponStaticReturn_ = !IsExplosion;
		}
		return;
	}

	ThrowStart(300); // 투사체를 던지고
	BulletMove(500, false); // 그게 날아가서
	IsExplosion = BulletColEvent(); // 충돌하면 이벤트가 발생한다.

	AirBombExplodEnd_ = !IsExplosion;

	if (BombCount_ == 2)
	{
		WeaponCameraPos_ = GetPosition();
		WeaponStaticReturn_ = IsExplosion;
	}
}

bool AirBomb::WeaponUpdate()
{
	return false;
}

void AirBomb::ResgistBomb()
{
	WeaponMaster::AirBombArr_[BombCount_] = this;
}