#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>



// Ό³Έν :
class GameEngineRenderer;
class LobbyShootingStarParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbyShootingStarParticle();
	~LobbyShootingStarParticle();

	// delete Function
	LobbyShootingStarParticle(const LobbyShootingStarParticle& _Other) = delete;
	LobbyShootingStarParticle(LobbyShootingStarParticle&& _Other) noexcept = delete;
	LobbyShootingStarParticle& operator=(const LobbyShootingStarParticle& _Other) = delete;
	LobbyShootingStarParticle& operator=(LobbyShootingStarParticle&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;


private:
	GameEngineRenderer* StarRenderer_;
	float CosAngle_;
};

