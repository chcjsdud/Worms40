#pragma once
#include "EffectManager.h"

// Ό³Έν :
class Skidmark : public EffectManager
{
public:
	// constrcuter destructer
	Skidmark();
	~Skidmark();

	// delete Function
	Skidmark(const Skidmark& _Other) = delete;
	Skidmark(Skidmark&& _Other) noexcept = delete;
	Skidmark& operator=(const Skidmark& _Other) = delete;
	Skidmark& operator=(Skidmark&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
};

