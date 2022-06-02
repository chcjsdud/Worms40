#include "PixelCollision.h"
#include "GameMapMaster.h"
#include<GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>



PixelCollision::PixelCollision()
{
}

PixelCollision::~PixelCollision()
{
}


void PixelCollision::Start()
{
	for (int i = 0; i < 8; i++)
	{
		ColorFlag_[i] = false;
	}

	BounceFlg_ = false;
}

void PixelCollision::Update()
{
}

void PixelCollision::Render()
{
}



//
float4 PixelCollision::Bounce(float4 _ActorPos,float4 _ActorScale,GameEngineImage* _ColMapImage,float4 _BulletDir)
{
	float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };


	//좌상단
	int TopLeftColor = _ColMapImage->GetImagePixel(_ActorPos + TopLeft);
	//상단
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//우상단
	int TopRightColor = _ColMapImage->GetImagePixel(_ActorPos + TopRight);
	//우측
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//우하단
	int BottomRightColor = _ColMapImage->GetImagePixel(_ActorPos + BottomRight);
	//하단
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//좌하단
	int BottomLeftColor = _ColMapImage->GetImagePixel(_ActorPos + BottomLeft);
	//좌측
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);

	// 함수가 시작될때 false로 설정
	BounceFlg_ = false;

	if (RGB(0, 0, 255) == TopColor && ColorFlag_[0] == false)
	{
		_BulletDir *= float4{1,-1};
		ColorFlag_[0] = true;
	}
	else
	{
		ColorFlag_[0] = false;
	}


	if (RGB(0, 0, 255) == RightColor && ColorFlag_[2] == false)
	{
		_BulletDir *= float4{ -1,1 };
		ColorFlag_[2] = true;
	}
	else
	{
		ColorFlag_[2] = false;
	}

	if (RGB(0, 0, 255) == BottomColor && ColorFlag_[4] == false)
	{
		_BulletDir *= float4{ 1,-1 };
		ColorFlag_[4] = true;
	}
	else
	{
		ColorFlag_[4] = false;
	}


	if (RGB(0, 0, 255) == LeftColor && ColorFlag_[6] == false)
	{
		_BulletDir *= float4{ -1,1 };
		ColorFlag_[6] = true;
	}
	else
	{
		ColorFlag_[6] = false;
	}

	for (int i = 0; i < 8; i++)
	{
		if (ColorFlag_[i] == true)
		{
			BounceFlg_ = true;
			break;
		}

		BounceFlg_ = false;
	}

	return _BulletDir;



}

float4 PixelCollision::PlayerBounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _MoveDir)
{
	float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };


	//좌상단
	int TopLeftColor = _ColMapImage->GetImagePixel(_ActorPos + TopLeft);
	//상단
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//우상단
	int TopRightColor = _ColMapImage->GetImagePixel(_ActorPos + TopRight);
	//우측
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//우하단
	int BottomRightColor = _ColMapImage->GetImagePixel(_ActorPos + BottomRight);
	//하단
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//좌하단
	int BottomLeftColor = _ColMapImage->GetImagePixel(_ActorPos + BottomLeft);
	//좌측
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);

	if (RGB(0, 0, 255) == TopColor && ColorFlag_[0] == false)
	{
		_MoveDir *= float4{ 1,-1 };
		ColorFlag_[0] = true;
	}
	else
	{
		ColorFlag_[0] = false;
	}


	if (RGB(0, 0, 255) == RightColor && ColorFlag_[2] == false)
	{
		_MoveDir *= float4{ -1,1 };
		ColorFlag_[2] = true;
	}
	else
	{
		ColorFlag_[2] = false;
	}

	if (RGB(0, 0, 255) == LeftColor && ColorFlag_[6] == false)
	{
		_MoveDir *= float4{ -1,1 };
		ColorFlag_[6] = true;
	}
	else
	{
		ColorFlag_[6] = false;
	}

	for (int i = 0; i < 8; i++)
	{
		if (ColorFlag_[i] == true)
		{
			BounceFlg_ = true;
			break;
		}

		BounceFlg_ = false;
	}

	return _MoveDir;

}

