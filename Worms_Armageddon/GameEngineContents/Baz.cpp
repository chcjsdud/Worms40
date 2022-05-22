#include "Baz.h"
#include "Enums.h"
#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameENgine/GameEngine.h>

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

	int Color = GetGameMap()->GetColMap()->GetImagePixel({GetPosition()});

	// 맵과 충돌처리
	if (RGB(0, 0, 255) == Color)
	{
		// 이미지를 가져와서 땅이 파여있는 상태를 메모리에 보존?
		// 바닥
		GameEngineImage* tmpGroundMap = GetGameMap()->GetGround()->GetImage();
		// 충돌
		GameEngineImage* tmpColMap = GetGameMap()->GetColMap();
		
		// tmpGoundMap, tmpColMap에 {255, 0, 255}의 원 그리기처리
		// tmpGroundMap->TransCopy(마젠타 원 이미지, , , , { 255, 0, 255 });
		// tmpColMap->TransCopy(원 이미지, , , ,{ 255, 0, 255 });

		// {255, 0, 255}의 원이 그려진 tmpGoundMap를 메인버퍼에 transCopy?\
		// 어차피 다음 프레임에는 업데이트 될테니 필요 없을수도?
		// -> 이러면 결국 마젠타부분은 그려지지 않을테니 의미없는것 같기도...


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
