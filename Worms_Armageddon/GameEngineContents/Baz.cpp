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
	WeaponRender_ = CreateRenderer("bazTest.bmp", 1);
	WeaponRender_->SetPivot({ 100,100 });
	WeaponRender_->SetIndex(0);
}

void Baz::Update()
{

}

void Baz::Render()
{

}