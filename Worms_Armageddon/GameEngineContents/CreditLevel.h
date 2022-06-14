#pragma once
#include "Credit.h"
#include "FadeIn.h"
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class CreditLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CreditLevel();
	~CreditLevel();

	// delete Function
	CreditLevel(const CreditLevel& _Other) = delete;
	CreditLevel(CreditLevel&& _Other) noexcept = delete;
	CreditLevel& operator=(const CreditLevel& _Other) = delete;
	CreditLevel& operator=(CreditLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;


private:
	Credit* Credit_;
	FadeIn* FadeIn_;

};

