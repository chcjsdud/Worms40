#pragma once
#include "EffectManager.h"

// Ό³Έν :
class Circle50 : public EffectManager
{
public:
	// constrcuter destructer
	Circle50();
	~Circle50();

	// delete Function
	Circle50(const Circle50& _Other) = delete;
	Circle50(Circle50&& _Other) noexcept = delete;
	Circle50& operator=(const Circle50& _Other) = delete;
	Circle50& operator=(Circle50&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
};

