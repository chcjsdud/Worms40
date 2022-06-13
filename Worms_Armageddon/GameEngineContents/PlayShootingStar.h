#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ShootingParticle.h"


// Ό³Έν :
class PlayShootingStar : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayShootingStar();
	~PlayShootingStar();

	// delete Function
	PlayShootingStar(const PlayShootingStar& _Other) = delete;
	PlayShootingStar(PlayShootingStar&& _Other) noexcept = delete;
	PlayShootingStar& operator=(const PlayShootingStar& _Other) = delete;
	PlayShootingStar& operator=(PlayShootingStar&& _Other) noexcept = delete;

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

