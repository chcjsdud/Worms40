#include "PixelCollision.h"
#include "GameMapMaster.h"
#include<GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>



void PixelCollision::CheckPixel(CheckType _MyType,float4 _MyPos, float4 _MyScale, GameEngineImage* _ColMapImage)
{

	switch (_MyType)
	{
	case CheckType::None:
		return;
	case CheckType::Player:

		break;
	case CheckType::WeaponMissile:
		bMissile = CheckMissilePixelCollision();
		break;
	case CheckType::WeaponGrenade:
		bGrenade = Bounce(_MyPos,_MyScale, _ColMapImage);
		break;
	default:
		break;
	}
}

void PixelCollision::Start()
{
	
}

void PixelCollision::Update()
{
}

void PixelCollision::Render()
{
}

bool PixelCollision::CheckMissilePixelCollision()
{
	return true;
}



//
bool PixelCollision::Bounce(float4 _ActorPos,float4 _ActorScale,GameEngineImage* _ColMapImage)
{
	//float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	//float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	//float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	//float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };


	//좌상단
	//int TopLeftColor = ColMapImage_->GetImagePixel(_ActorPos + TopLeft);
	//상단
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//우상단
	//int TopRightColor = ColMapImage_->GetImagePixel(_ActorPos + TopRight);
	//우측
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//우하단
	//int BottomRightColor = ColMapImage_->GetImagePixel(_ActorPos + BottomRight);
	//하단
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//좌하단
	//int BottomLeftColor = ColMapImage_->GetImagePixel(_ActorPos + BottomLeft);
	//좌측
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);

	if (RGB(0, 0, 255) == LeftColor ||
		RGB(0, 0, 255) == RightColor ||
		RGB(0, 0, 255) == BottomColor ||
		RGB(0, 0, 255) == TopColor)
	{
		return true;
	}
	return false;




}

