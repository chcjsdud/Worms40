#include "Sheep.h"
#include "SuperSheep.h"
#include "PixelCollision.h"
#include "TimerBox.h"
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

	SelfDestructSec_ = 8.f;
}

void Sheep::Update()
{

}

bool Sheep::WeaponUpdate()
{
	if (true == WeaponMaster::IsBulletOutofBound()) // 바다에 빠지면
	{
		if (nullptr != TimerBox_)
		{
			GetTimerBox()->DeleteGrenadeBox();
		}
		Off();
		return false;
	}

	if (SelfDestructSec_-5.f < GetAccTime() && false == IsTimerCreate_) // 타이머 박스 생성
	{
		CreateTimerBox(MyTeamColor_);
		IsTimerCreate_ = true;
	}

	if (SelfDestructSec_ < GetAccTime()) // 자동자폭
	{
		GetTimerBox()->DeleteGrenadeBox();
		Explosion();

		return false;
	}
	
	//타이머 박스 위치
	if (GetTimerBox() != nullptr)
	{
		GetTimerBox()->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE)) // 자폭
	{
		if (nullptr != TimerBox_)
		{
			GetTimerBox()->DeleteGrenadeBox();
		}
		Explosion();
		return false;
	}

	if (1 == ShotDir_.x) // 양이 바라보는 방향이 오른쪽
	{
		WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
	}

	ThrowStart(0); // 투사체를 던지고
	AnimalMove(); // 양이 움직이다가

	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}
