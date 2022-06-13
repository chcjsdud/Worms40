#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

enum class CreateStar
{
	SetTimer,
	AddTime,
	Create
};

// 설명 :
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


private :
	GameEngineRenderer* StarRenderer_;

	float CosAngle_;
	float LimitY_;
	float Speed_;

	float4 MoveDirection_;

public:
	void SetDirectionLeft(float4 _Direction); // true 라면 오른쪽 , false 왼쪽
	void SetDeleteY(float _PosY);
	void SetSpeed(float _SetSpeed);
	
};

