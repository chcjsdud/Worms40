#include "Sheep.h"
#include "SuperSheep.h"
#include "PixelCollision.h"
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
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
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
	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	if (WeaponState::SuperSheep == WState_) // 슈퍼양으로 변신
	{
		if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
		{
			SuperSheep* SS = GetLevel()->CreateActor<SuperSheep>();
			SS->SetPosition(GetPosition());
			Off();
		}
	}

	if (1 == ShotDir_.x) // 양이 바라보는 방향이 오른쪽
	{
		WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
	}


	ThrowStart(0); // 투사체를 던지고
	AnimalMove(); // 양이 움직이다가
	//BulletColEvent();

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}