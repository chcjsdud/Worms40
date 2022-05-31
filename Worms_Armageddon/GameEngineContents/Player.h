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

	inline bool GetIsDeath()
	{
		return IsDeath_;
	}

	inline bool GetIsTurnEnd()
	{
		return IsTurnEnd_;
	}

	PlayerState GetPlayerState() const
	{
		return CurrentState_;
	}

	float4 GetWeaponPos() const
	{
		return WeaponPos_;
	}

	bool ControllUpdate();
	void UnControllUpdate();
private:

	bool IsTurnEnd_;

	// �ӵ�
	float Speed_;
	// ���� �ӵ�
	float FallSpeed_;
	// ���� �Ÿ�
	float FallLength_;
	//���� �ӵ�
	float JumpSpeed_;
	//���� �Ÿ�
	float JumpDelayTime_;
	// ���� ����
	WeaponState WeaponState_;
	// ���� ��ġ
	float4 WeaponPos_;

	// �÷��̾� Hp
	int PlayerHp_;

	// �÷��̾� ��� �÷���
	bool IsDeath_;

	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;
	float4 JumpMoveDir_;

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
	std::string CurDirName_;

	// ���� ����
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// �ִϸ��̼� �ʱ�ȭ
	void PlayerAnimationInit();
	// Ű �ʱ�ȭ
	void PlayerKeyInit();

	//Ű �Է� ī��Ʈ
	int KeyCount_;
	float KeyTimer_;

	// Ű�Է� ���� �Լ�
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();
	bool IsJumpKeyDown();
	bool IsBackFlipKeyDown();
	bool IsBackFlipKeyFree();

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
	// ���� ����
	PlayerState PrevState_;

	void IdleStart();
	void MoveStart();
	void ActionStart();
	void JumpStart();
	void BackFlipStart();
	void FalledStart();

	void IdleUpdate();
	void MoveUpdate();
	void ActionUpdate();
	void JumpUpdate();
	void BackFlipUpdate();
	void FalledUpdate();

	void PlayerAnimationChange(std::string _Anim);
	
};

