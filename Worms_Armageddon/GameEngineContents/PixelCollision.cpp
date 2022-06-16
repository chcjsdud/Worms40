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
float4 PixelCollision::Bounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _BulletDir)
{
	float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };


	//�»��
	int TopLeftColor = _ColMapImage->GetImagePixel(_ActorPos + TopLeft);
	//���
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//����
	int TopRightColor = _ColMapImage->GetImagePixel(_ActorPos + TopRight);
	//����
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//���ϴ�
	int BottomRightColor = _ColMapImage->GetImagePixel(_ActorPos + BottomRight);
	//�ϴ�
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//���ϴ�
	int BottomLeftColor = _ColMapImage->GetImagePixel(_ActorPos + BottomLeft);
	//����
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);

	// �Լ��� ���۵ɶ� false�� ����
	BounceFlg_ = false;

	if (RGB(0, 0, 255) == TopColor && ColorFlag_[0] == false)
	{
		_BulletDir *= float4{ 1,-1 };
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

float4 PixelCollision::PlayerBounce(float4 _ActorPos, float4 _ActorScale,
	GameEngineImage* _ColMapImage, float4 _MoveDir,float _JumpSpeed)
{
	float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };

	//��ġ üũ��
	MoveDir_ = _MoveDir;

	//�»��
	int TopLeftColor = _ColMapImage->GetImagePixel(_ActorPos + TopLeft);
	//���
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//����
	int TopRightColor = _ColMapImage->GetImagePixel(_ActorPos + TopRight);
	//����
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//���ϴ�
	int BottomRightColor = _ColMapImage->GetImagePixel(_ActorPos + BottomRight);
	//�ϴ�
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//���ϴ�
	int BottomLeftColor = _ColMapImage->GetImagePixel(_ActorPos + BottomLeft);
	//����
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);


	//�÷��̾�� ������ �¿��̵� , �����̵� �ι��� �ϴµ�
	//ó���� �¿��̵��� üũ���� , ColorFlag�� true�ΰ͵���
	//false�� �ʱ�ȭ
	for (int i = 0; i < 8; i++)
	{
		ColorFlag_[i] = false;
	}


	//������ �浹��
	if (RGB(0, 0, 255) == TopColor && ColorFlag_[0] == false)
	{
		ColorFlag_[0] = true;
	}
	else
	{
		ColorFlag_[0] = false;
	}


	if (ColorFlag_[0] == true)
	{
		if (RGB(0, 0, 255) == TopLeftColor)
		{
			ColorFlag_[7] = true;
		}
		else
		{
			ColorFlag_[7] = false;
		}

		if (RGB(0, 0, 255) == TopRightColor)
		{
			ColorFlag_[1] = true;
		}
		else
		{
			ColorFlag_[1] = false;
		}
	}


	//������ �浹��
	if (ColorFlag_[0] == true && ColorFlag_[7] == true && ColorFlag_[1] == true)
	{
		float4 Dir = _ActorPos - (_ActorPos + Top);
		Dir.Normal2D();
		_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed};
		return _MoveDir;
	}
	else if (ColorFlag_[0] == true && ColorFlag_[7] == true && ColorFlag_[1] == false) //���, �»�� �浹��
	{
		if (RGB(0, 0, 255) == LeftColor) //���ʵ� �浹�ϸ� �밢������
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + Left.x) / 2,(Top.y + Left.y) / 2 });
			Dir.Normal2D();
			_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
			return _MoveDir;
		}
		else
		{  //���� �밢 / <-�̰���
			float4 Dir = _ActorPos - (_ActorPos + float4{(Top.x + TopLeft.x) / 2,(Top.y + TopLeft.y) / 2});
			Dir.Normal2D();
			_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
			return _MoveDir;
		}
	}
	else if (ColorFlag_[0] == true && ColorFlag_[7] == false && ColorFlag_[1] == true) //������
	{
		if (RGB(0, 0, 255) == RightColor)
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + Right.x) / 2,(Top.y + Right.y) / 2 });
			Dir.Normal2D();
			_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
			return _MoveDir;
		}
		else
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + TopRight.x) / 2,(Top.y + TopRight.y) / 2 });
			Dir.Normal2D();
			_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
			return _MoveDir;
		}
	}


	//�������� �浹��
	if (RGB(0, 0, 255) == RightColor && ColorFlag_[2] == false)
	{
		ColorFlag_[2] = true;
		float4 Dir = { _ActorPos.x - Right.x , _MoveDir.y };
		Dir.Normal2D();
		_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
		return _MoveDir;
	}
	else
	{
		ColorFlag_[2] = false;
	}


	//������ �浹��
	if (RGB(0, 0, 255) == LeftColor && ColorFlag_[6] == false)
	{
		ColorFlag_[6] = true;
		float4 Dir =  {_ActorPos.x - Left.x , _MoveDir.y};
		Dir.Normal2D();
		_MoveDir = float4{ Dir.x * (_JumpSpeed - 100.0f), Dir.y * _JumpSpeed };
		return _MoveDir;
	}
	else
	{
		ColorFlag_[6] = false;
	}




	////�浹����ġ�� �����ϸ� bounceFlg == true
	//for (int i = 0; i < 8; i++)
	//{
	//	if (ColorFlag_[i] == true)
	//	{
	//		BounceFlg_ = true;
	//		break;
	//	}

	//	BounceFlg_ = false;
	//}

	return _MoveDir;

}




float4 PixelCollision::PlayerFlyBounce(float4 _ActorPos, float4 _ActorScale,
	GameEngineImage* _ColMapImage, float4 _MoveDir, float _FlySpeed)
{
	float4 TopLeft = { -_ActorScale.x / 2 , -_ActorScale.y / 2 };
	float4 Top = { 0.0f , -_ActorScale.y / 2 };
	float4 TopRight = { _ActorScale.x / 2 , -_ActorScale.y / 2 };

	float4 Right = { _ActorScale.x / 2 , 0.0f };

	float4 BottomRight = { _ActorScale.x / 2 , _ActorScale.y / 2 };
	float4 Bottom = { 0.0f , _ActorScale.y / 2 };
	float4 BottomLeft = { -_ActorScale.x / 2 , _ActorScale.y / 2 };

	float4 Left = { -_ActorScale.x / 2 , 0.0f };

	//��ġ üũ��
	MoveDir_ = _MoveDir;

	//�»��
	int TopLeftColor = _ColMapImage->GetImagePixel(_ActorPos + TopLeft);
	//���
	int TopColor = _ColMapImage->GetImagePixel(_ActorPos + Top);
	//����
	int TopRightColor = _ColMapImage->GetImagePixel(_ActorPos + TopRight);
	//����
	int RightColor = _ColMapImage->GetImagePixel(_ActorPos + Right);
	//���ϴ�
	int BottomRightColor = _ColMapImage->GetImagePixel(_ActorPos + BottomRight);
	//�ϴ�
	int BottomColor = _ColMapImage->GetImagePixel(_ActorPos + Bottom);
	//���ϴ�
	int BottomLeftColor = _ColMapImage->GetImagePixel(_ActorPos + BottomLeft);
	//����
	int LeftColor = _ColMapImage->GetImagePixel(_ActorPos + Left);


	//�÷��̾�� ������ �¿��̵� , �����̵� �ι��� �ϴµ�
	//ó���� �¿��̵��� üũ���� , ColorFlag�� true�ΰ͵���
	//false�� �ʱ�ȭ
	for (int i = 0; i < 8; i++)
	{
		ColorFlag_[i] = false;
	}


	//������ �浹��
	if (RGB(0, 0, 255) == TopColor && ColorFlag_[0] == false)
	{
		ColorFlag_[0] = true;
	}
	else
	{
		ColorFlag_[0] = false;
	}


	if (ColorFlag_[0] == true)
	{
		if (RGB(0, 0, 255) == TopLeftColor)
		{
			ColorFlag_[7] = true;
		}
		else
		{
			ColorFlag_[7] = false;
		}

		if (RGB(0, 0, 255) == TopRightColor)
		{
			ColorFlag_[1] = true;
		}
		else
		{
			ColorFlag_[1] = false;
		}
	}


	//������ �浹��
	if (ColorFlag_[0] == true && ColorFlag_[7] == true && ColorFlag_[1] == true)
	{
		float4 Dir = _ActorPos - (_ActorPos + Top);
		Dir.Normal2D();
		_MoveDir = Dir * _FlySpeed * 0.5f;
		return _MoveDir;
	}
	else if (ColorFlag_[0] == true && ColorFlag_[7] == true && ColorFlag_[1] == false) //���, �»�� �浹��
	{
		if (RGB(0, 0, 255) == LeftColor) //���ʵ� �浹�ϸ� �밢������
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + Left.x) / 2,(Top.y + Left.y) / 2 });
			Dir.Normal2D();
			_MoveDir = Dir * _FlySpeed * 0.5f;
			return _MoveDir;
		}
		else
		{  //���� �밢 / <-�̰���
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + TopLeft.x) / 2,(Top.y + TopLeft.y) / 2 });
			Dir.Normal2D();
			_MoveDir = Dir * _FlySpeed * 0.5f;
			return _MoveDir;
		}
	}
	else if (ColorFlag_[0] == true && ColorFlag_[7] == false && ColorFlag_[1] == true) //������
	{
		if (RGB(0, 0, 255) == RightColor)
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + Right.x) / 2,(Top.y + Right.y) / 2 });
			Dir.Normal2D();
			_MoveDir = Dir * _FlySpeed * 0.5f;
			return _MoveDir;
		}
		else
		{
			float4 Dir = _ActorPos - (_ActorPos + float4{ (Top.x + TopRight.x) / 2,(Top.y + TopRight.y) / 2 });
			Dir.Normal2D();
			_MoveDir = Dir * _FlySpeed * 0.5f;
			return _MoveDir;
		}
	}


	//�������� �浹��
	if (RGB(0, 0, 255) == RightColor && ColorFlag_[2] == false)
	{
		ColorFlag_[2] = true;
		float4 Dir = { _ActorPos.x - Right.x , _MoveDir.y };
		Dir.Normal2D();
		_MoveDir = Dir * _FlySpeed * 0.5f;
		return _MoveDir;
	}
	else
	{
		ColorFlag_[2] = false;
	}


	//������ �浹��
	if (RGB(0, 0, 255) == LeftColor && ColorFlag_[6] == false)
	{
		ColorFlag_[6] = true;
		float4 Dir = { _ActorPos.x - Left.x , _MoveDir.y };
		Dir.Normal2D();
		_MoveDir = Dir * _FlySpeed * 0.5f;
		return _MoveDir;
	}
	else
	{
		ColorFlag_[6] = false;
	}


	return _MoveDir;

}

