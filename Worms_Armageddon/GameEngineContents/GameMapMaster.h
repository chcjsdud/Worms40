#pragma once
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include "LargeCloud.h"
#include "MiddleCloud.h"
#include "SmallCloud.h"
#include "Water.h"

// ���� :
class GameEngineImage;
class GameEngineRenderer;
class GameMapMaster : public GameEngineActor
{
public:
	// constrcuter destructer
	GameMapMaster();
	~GameMapMaster();

	// delete Function
	GameMapMaster(const GameMapMaster& _Other) = delete;
	GameMapMaster(GameMapMaster&& _Other) noexcept = delete;
	GameMapMaster& operator=(const GameMapMaster& _Other) = delete;
	GameMapMaster& operator=(GameMapMaster&& _Other) noexcept = delete;

	inline GameEngineImage* GetColMap()
	{
		return ColMap_;
	}

	inline GameEngineRenderer* GetBackGround()
	{
		return BackGround_;
	}

	inline GameEngineRenderer* GetColMapRender()
	{
		return ColMapRenderer_;
	}

	inline GameEngineRenderer* GetGround()
	{
		return Ground_;
	}

	inline float4 GetResponPosition(int i)
	{
		return ResponPosition_[i];
	}

	inline void SetPosFlg(bool _Flg, int _ArrI)
	{
		PositionFlg_[_ArrI] = _Flg;
	}

	inline bool GetPosFlg(int _ArrI)
	{
		return PositionFlg_[_ArrI];
	}

	void SetLargeCloudDir(int  _WindDir, float _CloudSpeed)
	{
		for (int i = 0; i < 4; i++)
		{
			LargeCloudActor_[i]->SetLargeCloudDir(_WindDir, _CloudSpeed);
		}
	}

	void SetMiddleCloudDir(int  _WindDir, float _CloudSpeed)
	{
		for (int i = 0; i < 3; i++)
		{
			MiddleCloudActor_[i]->SetMiddleCloudDir(_WindDir, _CloudSpeed);
		}
	}

	void SetSmallCloudDir(int  _WindDir, float _CloudSpeed)
	{
		for (int i = 0; i < 5; i++)
		{
			SmallCloudActor_[i]->SetSmallCloudDir(_WindDir, _CloudSpeed);
		}
	}

protected:
	void Start() override {};
	void Update() override {};

	// ����
	GameEngineRenderer* BackGround_;
	// �ٴ�
	GameEngineRenderer* Ground_;

	GameEngineRenderer* ColMapRenderer_;

	// �ʿ� ���� �浹�� �̹���
	GameEngineImage* ColMap_;

	float4 ResponPosition_[PLAYER_MAX_NUMBER];
	bool PositionFlg_[PLAYER_MAX_NUMBER];
	
	// �ٴںκ� �� �̹���
	Water* WaterActor_;

	// ���� �̹���
	LargeCloud* LargeCloudActor_[4];
	MiddleCloud* MiddleCloudActor_[3];
	SmallCloud* SmallCloudActor_[5];
};

