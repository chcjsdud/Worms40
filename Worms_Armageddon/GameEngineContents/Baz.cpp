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

	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
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

	// �ʰ� �浹ó��
	if (RGB(0, 0, 255) == Color)
	{
		// �̹����� �����ͼ� ���� �Ŀ��ִ� ���¸� �޸𸮿� ����?
		// �ٴ�
		GameEngineImage* tmpGroundMap = GetGameMap()->GetGround()->GetImage();
		// �浹
		GameEngineImage* tmpColMap = GetGameMap()->GetColMap();
		GameEngineImage* tmpEffectImg = GameEngineImageManager::GetInst()->Find(IMG_EFFECT_BOOM);

		// {0, 255, 0}�� ���� �׷��� tmpGoundMap�� ���ι��ۿ� transCopy
		// tmpGoundMap�� {0, 255, 0}�� �� �׸���ó��
		tmpGroundMap->TransCopy(tmpEffectImg, // _Other
			{GetPosition().x - SCALE_EFFECT_BOOM_X / 2, GetPosition().y - SCALE_EFFECT_BOOM_Y / 2, }, // _CopyPos
			tmpEffectImg->GetScale(), // _CopyScale
			{0, 0}, // _OtherPivot
			tmpEffectImg->GetScale(), // _OtherScale
			RGB( 0, 255, 0 ) // TransColor
		);

		// tmpColMap�� {0, 255, 0}�� �� �׸���ó��
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

	// ����
	//  ����
	//  ����
	//  ����
	// ���� ��
	return true;
}
