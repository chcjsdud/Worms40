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
	ThrowStart(0); // ����ü�� ������
	BulletMove(100, false); // �װ� ���ư���
	BulletColEvent(); // �浹�ϸ� �̺�Ʈ�� �߻��Ѵ�.

	if (BombCount_ == 2)
	{
		WeaponCameraPos_ = GetPosition();
	}
}

bool AirBomb::WeaponUpdate()
{
	return false;
}