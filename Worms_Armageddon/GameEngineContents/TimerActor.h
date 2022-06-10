#pragma once
#include <GameEngine/GameEngineActor.h>


// 설명 : GetACcTime, ResetAccTime만을 위한 액터
class TimerActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TimerActor();
	~TimerActor();

	// delete Function
	TimerActor(const TimerActor& _Other) = delete;
	TimerActor(TimerActor&& _Other) noexcept = delete;
	TimerActor& operator=(const TimerActor& _Other) = delete;
	TimerActor& operator=(TimerActor&& _Other) noexcept = delete;

protected:
	void Start() {};
private:

};

