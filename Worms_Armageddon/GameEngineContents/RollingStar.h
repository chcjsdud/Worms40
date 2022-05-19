#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class RollingStar : public GameEngineActor
{
public:
	// constrcuter destructer
	RollingStar();
	~RollingStar();

	// delete Function
	RollingStar(const RollingStar& _Other) = delete;
	RollingStar(RollingStar&& _Other) noexcept = delete;
	RollingStar& operator=(const RollingStar& _Other) = delete;
	RollingStar& operator=(RollingStar&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
private:
	class GameEngineRenderer* Renderer_;
};

