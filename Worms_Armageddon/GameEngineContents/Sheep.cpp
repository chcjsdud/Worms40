#include "Sheep.h"
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
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_LEFT, ANIM_NAME_SHEEP_LEFT, 0, 7, 0.04f);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_RIGHT, ANIM_NAME_SHEEP_RIGHT, 0, 7, 0.04f);
	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
}

void Sheep::Update()
{

}

bool Sheep::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	if (1 == ShotDir_.x) // ���� �ٶ󺸴� ������ ������
	{
		WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
	}

	if (WeaponState::SuperSheep == WState_)
	{

	}

	ThrowStart(0); // ����ü�� ������
	SheepMove(); // ���� �����̴ٰ�
	//BulletColEvent();

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}