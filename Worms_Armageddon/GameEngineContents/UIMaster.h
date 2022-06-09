#pragma once
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 : UI의 기능을 모아둔 부모클래스
class UIMaster : public GameEngineActor
{
public:
	void MoveSetting(float4 _StartPos, float4 _DestPos, float _Speed);
	void Move();
	bool IsMoveEnd()
	{
		if (STATE::IDLE == State_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	enum class STATE
	{
		IDLE,
		MOVING,
	};

protected:
	void UpdateState();

private:
	void ChangeState(STATE _State);

	void MovingStart();

	void IdleUpdate();
	void MovingUpdate();

private:
	STATE State_;

	// 이동 관련
	float DeltaTime_;
	float LerpDeltaTime_;
	float Speed_;
	float4 StartPos_;
	float4 DestPos_;
	float4 CurPos_;
	float4 MoveDir_;


protected:
	void Start() override;
	void Update() override;

public:
	// constrcuter destructer
	UIMaster();
	virtual ~UIMaster();

	// delete Function
	UIMaster(const UIMaster& _Other) = delete;
	UIMaster(UIMaster&& _Other) noexcept = delete;
	UIMaster& operator=(const UIMaster& _Other) = delete;
	UIMaster& operator=(UIMaster&& _Other) noexcept = delete;
};

