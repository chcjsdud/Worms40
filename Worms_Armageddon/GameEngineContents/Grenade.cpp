#include "Grenade.h"
#include "Enums.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Grenade::Grenade() 
	:
	GrenadeTimerBox_(nullptr)
{
}

Grenade::~Grenade() 
{
}

void Grenade::Start()
{
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("GrenadeSpin.bmp");
	WeaponRender_->SetRotationFilter("GrenadeSpinFilter.bmp");


}
void Grenade::Update()
{

}

bool Grenade::WeaponUpdate()
{
	// �Ѿ� 
	if (true == IsBulletOutofBound())
	{
		return false;
	}

	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	if (5.0f < GetAccTime()) // 5�� �� ����
	{
		Explosion();
		GrenadeTimerBox_->Death();
		return false;
	}

	ThrowStart(ShotPower_); // ����ü�� ������
	BulletMove(100, false); // �װ� ���ư���
	BulletColEvent(); // �浹�ϸ� �̺�Ʈ�� �߻��Ѵ�.

	//Ÿ�̸� �ڽ� ��ġ
	if (GrenadeTimerBox_ != nullptr)
	{
		GrenadeTimerBox_->TimerBoxSetPosition({this->GetPosition().x, this->GetPosition().y - 50.f});
	}


	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Grenade::CreateGrenadeTimerBox(TeamColor _Color)
{
	GrenadeTimerBox_ = GetLevel()->CreateActor<GrenadeTimerBox>();
	GrenadeTimerBox_->CreateGrenadeTimerBox(static_cast<FONT_COLOR>(_Color));
}

