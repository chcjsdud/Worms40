#pragma once
#include <GameEngine/GameEngineActor.h>

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

	inline GameEngineRenderer* GetGround()
	{
		return Ground_;
	}
protected:
	void Start() override {};
	void Update() override {};

	// ����
	GameEngineRenderer* BackGround_;
	// �ٴ�
	GameEngineRenderer* Ground_;

	// �ʿ� ���� �浹�� �̹���
	GameEngineImage* ColMap_;

};
