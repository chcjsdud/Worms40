#pragma once
#include "Enums.h"
#include "WeaponMaster.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>

// ���� :
class GameEngineImage;
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
	void Render() override;

	// ���� �ʱ� ����
public:
	inline void SetPlayerHp(int _WormzHp)
	{
		PlayerHp_ = _WormzHp;
	}
private:
	// �ӵ�
	float Speed_;
	// ���� �ӵ�
	float FallSpeed_;
	// ���� �Ÿ�
	float FallLength_;

	// �÷��̾� Hp
	int PlayerHp_;

	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;
	// ī�޶��� ��ġ
	float4 CameraPos_;
	// ���� ������Ʈ
	GameEngineSound* SoundPlayer_;

	// �÷��̾� ������
	GameEngineRenderer* PlayerRenderer_;

	// �÷��̾ �浹ó���� �� �� �̹���
	GameEngineImage* ColMapImage_;

	// �÷��̾ ��� �ִ� ������ Ÿ��
	int WeaponType_;
	// ������ ����
	WeaponMaster* Weapon_;

	std::string DirName_;
	std::string StateName_;

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
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();

	// �̵��� �浹üũ
	void MoveCheck(float4 _MoveDir);
	void MoveFall();
	//�������� �ȼ��浹üũ
	void CheckHillPixel();
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
	void ActionStart();
	void JumpStart();

	void IdleUpdate();
	void MoveUpdate();
	void ActionUpdate();
	void JumpUpdate();

	void PlayerAnimationChange(std::string _Anim);
	
};

