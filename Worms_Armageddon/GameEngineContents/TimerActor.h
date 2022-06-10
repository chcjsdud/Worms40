#pragma once
#include <GameEngine/GameEngineActor.h>


// ���� : GetACcTime, ResetAccTime���� ���� ����
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

