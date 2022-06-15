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
	if (true == WeaponMaster::IsBulletOutofBound()) // �ٴٿ� ������
	{
		Off();
		return false;
	}

	ThrowStart(ShotPower_); // ����ü�� ������
	BulletMove(500, true); // �װ� ���ư���
	BulletColEvent(); // �浹�ϸ� �̺�Ʈ�� �߻��Ѵ�.

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}
