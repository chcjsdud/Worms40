#pragma once
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class UIMaster : public GameEngineActor
{
public:
	void MoveSetting(float4 _StartPos, float4 _DestPos, float _Speed);
	void Move();

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

	void IdleUpdate();

	void MovingStart();
	void MovingUpdate();

private:
	STATE State_;

	float4 StartPos_;
	float4 DestPos_;
	float4 CurPos_;
	float4 MoveDir_;
	float Speed_;

	float DeltaTime_;

protected:
	void Start() override;
	void Update() override;
	//virtual void Render() {}

	//virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) {}
	//virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) {}
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

