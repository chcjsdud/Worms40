#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class GameEngineRenderer;
class Crosshair : public GameEngineActor
{
public:
	// constrcuter destructer
	Crosshair();
	~Crosshair();

	// delete Function
	Crosshair(const Crosshair& _Other) = delete;
	Crosshair(Crosshair&& _Other) noexcept = delete;
	Crosshair& operator=(const Crosshair& _Other) = delete;
	Crosshair& operator=(Crosshair&& _Other) noexcept = delete;
public:
	void UpdateCrosshairPos(float4 _PlayerPos, float4 _ShootVec);
protected:
	void Start() override;

private:
	GameEngineRenderer* Renderer_;
	float Distance_;
};

