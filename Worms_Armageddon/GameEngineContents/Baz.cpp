#include "Baz.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineInput.h>
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
	Dir_ = float4::UP * 100 + float4::RIGHT * 100;
}
void Baz::Update()
{

}
void Baz::Render()
{

}

bool Baz::WeaponUpdate()
{

	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ACTION))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	SetMove(Dir_ * GameEngineTime::GetDeltaTime());
	Dir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 100;

	// 동작
	//  동작
	//  동작
	//  동작
	// 동작 중
	return true;
}
