#pragma once
#include "EffectManager.h"

// ���� :
class Foom : public EffectManager
{
public:
	// constrcuter destructer
	Foom();
	~Foom();

	// delete Function
	Foom(const Foom& _Other) = delete;
	Foom(Foom&& _Other) noexcept = delete;
	Foom& operator=(const Foom& _Other) = delete;
	Foom& operator=(Foom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
};

