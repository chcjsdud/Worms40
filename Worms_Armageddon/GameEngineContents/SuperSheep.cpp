#include "SuperSheep.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PixelCollision.h"

SuperSheep::SuperSheep() 
{
}

SuperSheep::~SuperSheep() 
{
}

void SuperSheep::Start()
{
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage(IMG_SUPERSHEEP_FLY);
	WeaponRender_->SetIndex(0);
}

void SuperSheep::Update()
{

}



void SuperSheep::SuperFly()
{

}