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
	// 김성훈(지워주시면 됩니다)
	// 병합하고 올릴 때 에러나서 주석처리 잠깐 해 놓았습니다
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