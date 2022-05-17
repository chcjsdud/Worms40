#pragma once
#include "Enums.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>

// ���� :
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
	// �ӵ�
	float Speed_;
	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;
	// ī�޶��� ��ġ
	float4 CameraPos_;
	// ���� ������Ʈ
	GameEngineSound* SoundPlayer_;

	// �÷��̾� ������
	GameEngineRenderer* PlayerRenderer_;

	// ���� ����
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// �ִϸ��̼� �ʱ�ȭ
	void PlayerAnimationInit();
	// Ű �ʱ�ȭ
	void PlayerKeyInit();
	// ī�޶� ������Ʈ
	void UpdateCamera();

	// Ű�Է� ���� �Լ�
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	// FSM
public:
	// ������ȯ
	void StateChange(PlayerState _State);
	// ���� ������Ʈ
	void StateUpdate();
private:
	// ���� ����
	PlayerState CurrentState_;

	void IdleStart();
	void MoveStart();

	void IdleUpdate();
	void MoveUpdate();
};

