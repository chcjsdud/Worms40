#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

SuperSheep::SuperSheep() 
{
}

SuperSheep::~SuperSheep() 
{
}

void SuperSheep::Start()
{
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_LEFT, ANIM_NAME_SHEEP_LEFT, 0, 7, 0.04f);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_RIGHT, ANIM_NAME_SHEEP_RIGHT, 0, 7, 0.04f);
	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
}

void SuperSheep::Update()
{

}

bool SuperSheep::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	ThrowStart(0); // ����ü�� ������


	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}