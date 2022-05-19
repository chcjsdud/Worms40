#include "Baz.h"
#include "Enums.h"
#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Baz::Baz() 
	: IsStart_(false)
{
}

Baz::~Baz() 
{
}

void Baz::Start()
{
	WeaponRender_ = CreateRenderer(IMG_MISSILE, (int)RenderOrder::Weapon);
	WeaponRender_->SetIndex(0);
	BazDir_ += float4::UP * 100;
}
void Baz::Update()
{

}
void Baz::Render()
{

}

bool Baz::WeaponUpdate()
{
	if (false == IsStart_)
	{
		if (float4::LEFT.CompareInt2D(GetWeaponDir()))
		{
			BazDir_ += float4::LEFT * 100;
		}
		else
		{
			BazDir_ += float4::RIGHT * 100;
		}
		IsStart_ = true;
	}
	
	
	

	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ACTION))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}
	
	PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
	float4 Wind = Play->GetWindDir();
	

	SetMove(BazDir_ * GameEngineTime::GetDeltaTime());
	BazDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 100;
	BazDir_ += Wind * GameEngineTime::GetDeltaTime();
	

	// 동작
	//  동작
	//  동작
	//  동작
	// 동작 중
	return true;
}
