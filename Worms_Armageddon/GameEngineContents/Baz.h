#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class GameEngineRenderer;
class Baz : public WeaponMaster
{
public:
	// constrcuter destructer
	Baz();
	~Baz();

	// delete Function
	Baz(const Baz& _Other) = delete;
	Baz(Baz&& _Other) noexcept = delete;
	Baz& operator=(const Baz& _Other) = delete;
	Baz& operator=(Baz&& _Other) noexcept = delete;

	bool WeaponUpdate() override;

protected:
	void Start() override;
	void Update() override;
	void Render() override;


private:
	GameEngineRenderer* WeaponRender_;
	float4 Dir_;
};

