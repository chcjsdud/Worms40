#include "Sheep.h"
#include "SuperSheep.h"
#include "PixelCollision.h"
#include "TimerBox.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Sheep::Sheep() 
	: TimerBox_(nullptr)
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

	if (7.0f < GetAccTime()) // 20초 후 폭발
	{
		Explosion();
		TimerBox_->DeleteGrenadeBox();
		return false;
	}

	//타이머 박스 위치
	if (TimerBox_ != nullptr)
	{
		TimerBox_->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE)) // 자폭
	{
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

void Sheep::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), 20);
}
