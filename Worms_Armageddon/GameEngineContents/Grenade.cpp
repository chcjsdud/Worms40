#include "Grenade.h"
#include "Enums.h"
#include "PixelCollision.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Grenade::Grenade() 
	:
	TimerBox_(nullptr)
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
	// 총알 
	if (true == IsBulletOutofBound())
	{
		return false;
	}

	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	if (SelfDestructSec_ < GetAccTime()) // 자폭
	{
		Explosion();
		TimerBox_->DeleteGrenadeBox();
		return false;
	}

	ThrowStart(ShotPower_); // 투사체를 던지고
	BulletMove(500, false); // 그게 날아가서
	BulletColEvent(); // 충돌하면 이벤트가 발생한다.

	//타이머 박스 위치
	if (TimerBox_ != nullptr)
	{
		TimerBox_->TimerBoxSetPosition({this->GetPosition().x, this->GetPosition().y - 50.f});
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

void Grenade::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), SelfDestructSec_);
}

