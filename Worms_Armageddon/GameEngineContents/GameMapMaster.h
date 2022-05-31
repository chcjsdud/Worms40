#pragma once
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
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

protected:
	void Start() override {};
	void Update() override {};

	// 배경색
	GameEngineRenderer* BackGround_;
	// 바닥
	GameEngineRenderer* Ground_;

	GameEngineRenderer* ColMapRenderer_;

	// 맵에 사용될 충돌용 이미지
	GameEngineImage* ColMap_;

	float4 ResponPosition_[PLAYER_MAX_NUMBER];
	bool PositionFlg_[PLAYER_MAX_NUMBER];
};

