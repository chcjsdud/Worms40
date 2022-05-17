#pragma once
#include "Enums.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// 설명 :
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	// 속도
	float Speed_;
	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;
	// 카메라의 위치
	float4 CameraPos_;
	// 사운드 오브젝트
	GameEngineSound* SoundPlayer_;

	// 현재 레벨
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// 애니메이션 초기화
	void PlayerAnimationInit();
	// 키 초기화
	void PlayerKeyInit();
	// 카메라 업데이트
	void UpdateCamera();

	// 키입력 관련 함수
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	// FSM
public:
	// 상태전환
	void StateChange(PlayerState _State);
	// 상태 업데이트
	void StateUpdate();
private:
	// 현재 상태
	PlayerState CurrentState_;

	void IdleStart();
	void MoveStart();

	void IdleUpdate();
	void MoveUpdate();
};

