#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

enum class CreateStar
{
	SetTimer,
	AddTime,
	Create
};

// ���� :
class GameEngineRenderer;
class ShootingParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	ShootingParticle();
	~ShootingParticle();

	// delete Function
	ShootingParticle(const ShootingParticle& _Other) = delete;
	ShootingParticle(ShootingParticle&& _Other) noexcept = delete;
	ShootingParticle& operator=(const ShootingParticle& _Other) = delete;
	ShootingParticle& operator=(ShootingParticle&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;


private :
	GameEngineRenderer* StarRenderer_;

	float CosAngle_;
	float LimitY_;
	float Speed_;


	bool StarUpdate_;

	static float4 MoveDirection_;

public:
	void SetDirection(float4 _Direction); // true ��� ������ , false ����
	void SetDeleteY(float _PosY);
	void SetSpeed(float _SetSpeed);
	
	void SetStarAnimation();
	void SetLeafAnimation();

	void SetLeafCurve();

private:
	void StarUpdate();
	void LeafUpdate();
};

