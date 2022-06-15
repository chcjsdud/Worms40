#include "Sheep.h"
#include "SuperSheep.h"
#include "PixelCollision.h"
#include "TimerBox.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
Sheep::Sheep() 
{
}

Sheep::~Sheep() 
{
}

void Sheep::Start()
{
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_LEFT, ANIM_NAME_SHEEP_LEFT, 0, 7, 0.04f);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_RIGHT, ANIM_NAME_SHEEP_RIGHT, 0, 7, 0.04f);
	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);

	SelfDestructSec_ = 8.f;
}

void Sheep::Update()
{

}

bool Sheep::WeaponUpdate()
{
	if (true == WeaponMaster::IsBulletOutofBound()) // �ٴٿ� ������
	{
		if (nullptr != TimerBox_)
		{
			GetTimerBox()->DeleteGrenadeBox();
		}
		Off();
		return false;
	}

	if (SelfDestructSec_-5.f < GetAccTime() && false == IsTimerCreate_) // Ÿ�̸� �ڽ� ����
	{
		CreateTimerBox(MyTeamColor_);
		IsTimerCreate_ = true;
	}

	if (SelfDestructSec_ < GetAccTime()) // �ڵ�����
	{
		GetTimerBox()->DeleteGrenadeBox();
		Explosion();

		return false;
	}
	
	//Ÿ�̸� �ڽ� ��ġ
	if (GetTimerBox() != nullptr)
	{
		GetTimerBox()->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE)) // ����
	{
		if (nullptr != TimerBox_)
		{
			GetTimerBox()->DeleteGrenadeBox();
		}
		Explosion();
		return false;
	}

	if (1 == ShotDir_.x) // ���� �ٶ󺸴� ������ ������
	{
		WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
	}

	ThrowStart(0); // ����ü�� ������
	AnimalMove(); // ���� �����̴ٰ�

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}
