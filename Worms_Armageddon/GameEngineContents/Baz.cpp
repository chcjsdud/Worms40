#include "Baz.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Baz::Baz() 
{
}

Baz::~Baz() 
{
}

void Baz::Start()
{
	WeaponRender_ = CreateRenderer("bazAimLeft.bmp", 1);
	WeaponRender_->SetPivot({ 100,100 });
	// �輺��(�����ֽø� �˴ϴ�)
	// �����ϰ� �ø� �� �������� �ּ�ó�� ��� �� ���ҽ��ϴ�
	//WeaponRender_->SetIndex(0);
}

void Baz::Update()
{

}

void Baz::Render()
{
	int c = 0;

	int a = 0;
}