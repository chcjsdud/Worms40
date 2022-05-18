#pragma once
#include<GameEngine/GameEngineActor.h>

// Ό³Έν :
class LargeCloud	:public GameEngineActor
{
public:
	// constrcuter destructer
	LargeCloud();
	~LargeCloud();

	// delete Function
	LargeCloud(const LargeCloud& _Other) = delete;
	LargeCloud(LargeCloud&& _Other) noexcept = delete;
	LargeCloud& operator=(const LargeCloud& _Other) = delete;
	LargeCloud& operator=(LargeCloud&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* CloudRenderer_;
};

