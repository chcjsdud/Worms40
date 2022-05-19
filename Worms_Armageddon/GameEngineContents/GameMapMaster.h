#pragma once
#include <GameEngine/GameEngineActor.h>

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

	inline GameEngineRenderer* GetGround()
	{
		return Ground_;
	}
protected:
	void Start() override {};
	void Update() override {};

	// 배경색
	GameEngineRenderer* BackGround_;
	// 바닥
	GameEngineRenderer* Ground_;

	GameEngineRenderer* ColImage_;
	// 맵에 사용될 충돌용 이미지
	GameEngineImage* ColMap_;

};

