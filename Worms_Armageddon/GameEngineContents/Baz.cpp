#include "Baz.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Baz::Baz() 
{
}

Baz::~Baz() 
{
}

void Baz::Start()
{
	WeaponRender_ = CreateRenderer(IMG_MISSILE, (int)RenderOrder::Weapon);
	WeaponRender_->SetIndex(0);
}
void Baz::Update()
{

}
void Baz::Render()
{

}

bool Baz::WeaponUpdate()
{

	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ACTION))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	// ����
	//  ����
	//  ����
	//  ����
	// ���� ��
	return true;
}
