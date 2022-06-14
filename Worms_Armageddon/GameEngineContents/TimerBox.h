#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

enum class GrenadeTimerState
{
	Timer,
	ChangeFont,
	BorderChange
};

class TimerBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TimerBox();
	~TimerBox();

	// delete Function
	TimerBox(const TimerBox& _Other) = delete;
	TimerBox(TimerBox&& _Other) noexcept = delete;
	TimerBox& operator=(const TimerBox& _Other) = delete;
	TimerBox& operator=(TimerBox&& _Other) noexcept = delete;

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

	void DeleteGrenadeBox();
	
	void CreateTimerBox(FONT_COLOR _FontColor, int _Time);
};

