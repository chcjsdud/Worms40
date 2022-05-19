#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Water	:public GameEngineActor
{
public:
	// constrcuter destructer
	Water();
	~Water();

	// delete Function
	Water(const Water& _Other) = delete;
	Water(Water&& _Other) noexcept = delete;
	Water& operator=(const Water& _Other) = delete;
	Water& operator=(Water&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* WaterRenderer1_;
	GameEngineRenderer* WaterRenderer2_;
	GameEngineRenderer* WaterRenderer3_;
	GameEngineRenderer* WaterRenderer4_;
};

