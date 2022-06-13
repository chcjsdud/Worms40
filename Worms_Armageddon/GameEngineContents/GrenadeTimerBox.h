#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

enum class GrenadeTimerState
{
	Timer,
	ChangeFont,
	BorderChange
};

class GrenadeTimerBox : public GameEngineActor
{
public:
	// constrcuter destructer
	GrenadeTimerBox();
	~GrenadeTimerBox();

	// delete Function
	GrenadeTimerBox(const GrenadeTimerBox& _Other) = delete;
	GrenadeTimerBox(GrenadeTimerBox&& _Other) noexcept = delete;
	GrenadeTimerBox& operator=(const GrenadeTimerBox& _Other) = delete;
	GrenadeTimerBox& operator=(GrenadeTimerBox&& _Other) noexcept = delete;

protected:
	void Start();
	void Update();

private:
	GameEngineRenderer* TimerBox_;
	Font* TimerFont_;
	FONT_COLOR FontColor_;

	GrenadeTimerState TimerState_;

	int Timer_;			// 폰트용
	int StateTimer_;	// 스테이트용


public:
	//void SetFontColor(FONT_COLOR _FontColor);
	void TimerBoxSetPosition(float4 _Pos);
	
	void SetBoxBorder();
	void SetBoxThin();
	
	void CreateGrenadeTimerBox(FONT_COLOR _FontColor);
};

