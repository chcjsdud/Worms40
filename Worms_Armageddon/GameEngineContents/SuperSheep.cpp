#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>

SuperSheep::SuperSheep() 
{
}

SuperSheep::~SuperSheep() 
{
}

void SuperSheep::Start()
{

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

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}
