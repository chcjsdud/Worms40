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
	bool IsExplosion = true;

	ThrowStart(300); // ����ü�� ������
	BulletMove(500, false); // �װ� ���ư���
	IsExplosion = BulletColEvent(); // �浹�ϸ� �̺�Ʈ�� �߻��Ѵ�.



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