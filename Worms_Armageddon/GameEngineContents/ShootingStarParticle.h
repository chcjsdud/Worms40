#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>



// Ό³Έν :
class GameEngineRenderer;
class ShootingStarParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	ShootingStarParticle();
	~ShootingStarParticle();

	// delete Function
	ShootingStarParticle(const ShootingStarParticle& _Other) = delete;
	ShootingStarParticle(ShootingStarParticle&& _Other) noexcept = delete;
	ShootingStarParticle& operator=(const ShootingStarParticle& _Other) = delete;
	ShootingStarParticle& operator=(ShootingStarParticle&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;


private:
	GameEngineRenderer* StarRenderer_;
	float CosAngle_;
};

