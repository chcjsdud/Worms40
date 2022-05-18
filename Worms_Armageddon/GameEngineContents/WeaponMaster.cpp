#include "WeaponMaster.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

WeaponMaster::WeaponMaster() 
{
}

WeaponMaster::~WeaponMaster() 
{
}

void WeaponMaster::Start()
{
	WeaponRender_ = CreateRenderer("bazAimLeft.bmp", 1);
	WeaponRender_->SetPivot({ 100,100 });
	WeaponRender_->SetIndex(0);
}

void WeaponMaster::Update()
{

}

void WeaponMaster::Render()
{
	
}