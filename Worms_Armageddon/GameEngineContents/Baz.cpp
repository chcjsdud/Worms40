#include "Baz.h"
#include "Enums.h"
#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameENgine/GameEngine.h>

Baz::Baz()
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
}
void Baz::Update()
{
	
}
void Baz::Render()
{

}

bool Baz::WeaponUpdate()
{
	ThrowStart(100);

	// 테스트
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// 무기가 폭발하고 
		// 동작 끝 - > 플레이어의 State가 변경, 턴종료
		return false;
	}

	PlayLevel* Play = dynamic_cast<PlayLevel*>(GetLevel());
	float4 Wind = Play->GetWindDir();

	SetMove(BulletDir_ * GameEngineTime::GetDeltaTime());
	BulletDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 100;
	BulletDir_ += Wind * GameEngineTime::GetDeltaTime();

	float4 MyPos = GetPosition();
	float4 GetNextPos = BulletDir_ + GetPosition();


	float Degree = float4::VectorXYtoDegree(GetPosition(), GetPosition() + BulletDir_);
	WeaponRender_->SetRotationZ(Degree + 90);

	int Color = GetGameMap()->GetColMap()->GetImagePixel({GetPosition()});

	// 맵과 충돌처리
	if (RGB(0, 0, 255) == Color)
	{
		// 이미지를 가져와서 땅이 파여있는 상태를 메모리에 보존?
		// 바닥
		GameEngineImage* tmpGroundMap = GetGameMap()->GetGround()->GetImage();
		// 충돌
		GameEngineImage* tmpColMap = GetGameMap()->GetColMap();
		GameEngineImage* tmpEffectImg = GameEngineImageManager::GetInst()->Find(IMG_EFFECT_BOOM);

		// {0, 255, 0}의 원이 그려진 tmpGoundMap를 메인버퍼에 transCopy
		// tmpGoundMap에 {0, 255, 0}의 원 그리기처리
		tmpGroundMap->TransCopy(tmpEffectImg, // _Other
			{GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
			tmpEffectImg->GetScale(), // _CopyScale
			{0, 0}, // _OtherPivot
			tmpEffectImg->GetScale(), // _OtherScale
			RGB( 0, 255, 0 ) // TransColor
		);

		// tmpColMap에 {0, 255, 0}의 원 그리기처리
		tmpColMap->TransCopy(tmpEffectImg, // _Other
			{ GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
			tmpEffectImg->GetScale(), // _CopyScale
			{ 0, 0 }, // _OtherPivot
			tmpEffectImg->GetScale(), // _OtherScale
			RGB(0, 255, 0) // TransColor
		);


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
