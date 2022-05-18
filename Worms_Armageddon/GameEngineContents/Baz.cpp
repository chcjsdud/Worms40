#include "Baz.h"
#include "Enums.h"
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
