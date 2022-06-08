#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

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

	GameEngineRenderer* HpBar_;
	Font* HpFont_;

	FONT_COLOR FontColor_;
	int Hp_;


public:
	void ChangeHpBarFont(int _Num, float4 _Pivot);

	void SetFontColor(FONT_COLOR _FontColor);
	void SetHp(int _Hp);
	void HpBarSetPosition(float4 _Pos);



	FONT_COLOR GetFontColor()
	{
		return FontColor_;
	}


};

