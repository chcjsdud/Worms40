#include "Grenade.h"
#include "Enums.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Grenade::Grenade() 
{
}

Grenade::~Grenade() 
{
}

void Grenade::Start()
{
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("GrenadeSpin.bmp");
	WeaponRender_->SetRotationFilter("GrenadeSpinFilter.bmp");

	SelfDestructSec_ = 5.f;
}
void Grenade::Update()
{

}

bool Grenade::WeaponUpdate()
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

	if (SelfDestructSec_ - 5.f < GetAccTime() && false == IsTimerCreate_) // 타이머 박스 생성
	{
		CreateTimerBox(MyTeamColor_);
		IsTimerCreate_ = true;
	}

	if (SelfDestructSec_ < GetAccTime()) // 자폭
	{
		GetTimerBox()->DeleteGrenadeBox();
		Explosion();
		return false;
	}

	ThrowStart(ShotPower_); // 투사체를 던지고
	BulletMove(500, false); // 그게 날아가서
	BulletColEvent(); // 충돌하면 이벤트가 발생한다.

	//타이머 박스 위치
	if (GetTimerBox() != nullptr)
	{
		GetTimerBox()->TimerBoxSetPosition({this->GetPosition().x, this->GetPosition().y - 50.f});
	}


	if (false == IsUpdate()) // 웜즈가 체력이 깎인 후 false 리턴되도록 변경 예정
	{
		return false;
	}
	else
	{
		return true;
	}
}
