#include "Grenade.h"
#include "Enums.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Grenade::Grenade() 
	:
	TimerBox_(nullptr)
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

	SelfDestructSec_ = 5.f;
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

	if (SelfDestructSec_ < GetAccTime()) // ����
	{
		Explosion();
		TimerBox_->DeleteGrenadeBox();
		return false;
	}

	ThrowStart(ShotPower_); // ����ü�� ������
	BulletMove(500, false); // �װ� ���ư���
	BulletColEvent(); // �浹�ϸ� �̺�Ʈ�� �߻��Ѵ�.

	//Ÿ�̸� �ڽ� ��ġ
	if (TimerBox_ != nullptr)
	{
		TimerBox_->TimerBoxSetPosition({this->GetPosition().x, this->GetPosition().y - 50.f});
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

void Grenade::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), SelfDestructSec_);
}

