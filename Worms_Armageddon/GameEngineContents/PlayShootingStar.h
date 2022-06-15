#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ShootingParticle.h"


// 설명 :
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

	bool Dir_; //true 오른쪽 false 왼쪽

public:
	void SetLeftDir();
	void SetRightDir();
};

