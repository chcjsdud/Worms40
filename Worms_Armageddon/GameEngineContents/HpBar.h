#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>

// 설명 :Test용 마우스기능 
class HpBar : public GameEngineActor
{
public:
	// constrcuter destructer
	HpBar();
	~HpBar();

	// delete Function
	HpBar(const HpBar& _Other) = delete;
	HpBar(HpBar&& _Other) noexcept = delete;
	HpBar& operator=(const HpBar& _Other) = delete;
	HpBar& operator=(HpBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

};

