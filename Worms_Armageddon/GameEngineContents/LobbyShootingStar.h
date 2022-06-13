#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ShootingParticle.h"



// Ό³Έν :
class LobbyShootingStar : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbyShootingStar();
	~LobbyShootingStar();

	// delete Function
	LobbyShootingStar(const LobbyShootingStar& _Other) = delete;
	LobbyShootingStar(LobbyShootingStar&& _Other) noexcept = delete;
	LobbyShootingStar& operator=(const LobbyShootingStar& _Other) = delete;
	LobbyShootingStar& operator=(LobbyShootingStar&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	CreateStar CreateStarState_;
	GameEngineRandom RandomCreateTimer_;
	GameEngineRandom RandomPosX_;
	GameEngineRandom RandomPosY_;


	ShootingParticle* ShootingParticle_;
	
	float CreateTimer_;
};

