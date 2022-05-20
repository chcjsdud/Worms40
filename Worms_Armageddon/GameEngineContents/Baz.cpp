#include "Baz.h"
#include "Enums.h"
#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Baz::Baz()
	: IsStart_(false)
{
}

Baz::~Baz()
{
}

void Baz::Start()
{
	/*WeaponRender_ = CreateRenderer(IMG_MISSILE, (int)RenderOrder::Weapon);
	WeaponRender_->SetIndex(0);*/
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->SetImage("BazSpin.bmp");
	WeaponRender_->SetRotationFilter("BazSpinFilter.bmp");
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
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
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

	float4 MyPos = GetPosition();
	float4 GetNextPos = BazDir_ + GetPosition();


	//float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BazDir_);
	//WeaponRender_->SetRotationZ(Degree);

	int Color = GetColMapImage()->GetImagePixel({ GetPosition() });

	if (RGB(0, 0, 255) == Color)
	{
		Off();
		return false;


	}
	// 동작
	//  동작
	//  동작
	//  동작
	// 동작 중
	return true;
}
