#pragma once
#include "Enums.h"
#include "WeaponMaster.h"
#include "HpBar.h"
#include "Crosshair.h"
#include "ChargeBlob.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

// ���� :
class GameEngineImage;
class PixelCollision;
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

	inline bool GetIsDamagedCam() const
	{
		return IsDamagedCam_;
	}

	inline void SetIsDamagedCam(bool _IsDamagedCam)
	{
		IsDamagedCam_ = _IsDamagedCam;
	}

	inline int GetPlayerHp()
	{
		return PlayerHp_;
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

	inline void SetMyTeamColor(TeamColor _Color)
	{
		MyTeamColor_ = _Color;
		SetFontColor(static_cast<FONT_COLOR>(_Color));
	}


	inline void SetControlFlg(bool _ControlFlg)
	{
		ControlFlg_ = _ControlFlg;
	}

	inline void SetTurnEndFlg(bool _TurnEndFlg)
	{
		IsTurnEnd_ = _TurnEndFlg;
	}


	bool ControllUpdate();


	//������ üũ
	void Damaged(float4 _WeaponPos = float4::ZERO);
private:

	float FlySpeed_;

	bool IsTurnEnd_;
	
	//�������� �Ծ��� ���Ծ��� Ȯ���ϴ� flag
	bool IsDamaged_;
	bool IsDamagedCam_;
	//��� �������� ����
	int AllDamage_;
	int Damage_;
	// �ӵ�
	float Speed_;
	// ���� �ӵ�
	float FallSpeed_;
	float SlideFallspeed_;
	// ���� �Ÿ�
	float FallLength_;
	//���� �ӵ�
	float JumpSpeed_;
	//���������غ��� �ִϸ��̼� �÷���Ÿ��
	float JumpDelayTime_;
	// ���� ����
	WeaponState WeaponState_;
	WeaponState PrevWeaponState_;
	// ���� ��ġ
	float4 WeaponPos_;
	// ������ ������ ��ġ
	float4 ExplodWeaponPos_;
	// �ȼ� üũ
	PixelCollision* PixelCol_;
	// �÷��̾� Hp
	int PlayerHp_;

	bool IsGrave_;

	// ���� �� ���� ����
	TeamColor MyTeamColor_;

	// ���� �߻簢��
	float4 ShotAngle_;
	float4 ShotAngleMax_;
	float4 ShotAngleMin_;

	// ���� �߻� ��
	float ShotPower_;

	//����� �÷��̾� ������ �Ÿ�
	float Len_;

	// �÷��̾� ��� �÷���
	bool IsDeath_;

	bool IsJump_;
	//���� �ٲٴ� �ִϸ��̼� üũ��
	bool IsSwitch;

	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;
	//������ �¿����
	float4 JumpMoveDir_;
	//���󰡴� ����
	float4 FlyMoveDir_;

	// ���� ������Ʈ
	GameEngineSoundPlayer Sound_Walk;
	GameEngineSoundPlayer Sound_Fall;
	GameEngineSoundPlayer Sound_Jump;
	GameEngineSoundPlayer Sound_Backflip;
	GameEngineSoundPlayer Sound_Byebye;
	bool Sound_JumpOn;
	bool Sound_BackflipOn;

	static GameEngineRandom Ran;

	// �÷��̾� ������
	GameEngineRenderer* PlayerRenderer_;

	// �÷��̾ �浹ó���� �� �� �̹���
	GameEngineImage* ColMapImage_;

	// �÷��̾ ��� �ִ� ������ Ÿ��
	int WeaponType_;
	// ������ ����
	static WeaponMaster* Weapon_;

	// HpBar
	HpBar* Hpbar_;

	// �ൿ�� ȭ��ǥ ������
	GameEngineRenderer* ControlWorms_;

	// Crosshair
	Crosshair* Crshair_;

	// ChargeBlob
	ChargeBlob* CrgBlob_;

	//�ִϸ��̼ǿ� �����̸�
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
	//�÷��̾� ���� ó���Լ�
	void CheckDeath();


	bool ControlFlg_;
	float DeathDelayTime_;
	bool SlideEnd_;
	bool IsFly_;

	//Ű �Է� ī��Ʈ
	int KeyCount_;

	//Ű �Է� Ÿ�̸� ,  ����Ŭ����
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
	bool IsPlayerDeathKeyDown();



	// �̵��� �浹üũ
	void MoveCheck(float4 _MoveDir);
	// �߷�
	void MoveFall();
	//�������� �ȼ��浹üũ
	void CheckHillPixel();
public:
	// ������ȯ
	void StateChange(PlayerState _State);
	// ���� ������Ʈ
	void StateUpdate();
	void FlyAwayStart();
private:
	// ���� ����
	PlayerState CurrentState_;
	// ���� ����
	PlayerState PrevState_;

	//
	PlayerUnControlState UnControlState_;

	void IdleStart();
	void WeaponSwapStart();
	void MoveStart();
	void ActionStart();
	void JumpStart();
	void BackFlipStart();
	void FalledStart();
	void DeathStart();
	void SlideStart();



	void IdleUpdate();
	void WeaponSwapUpdate();
	void MoveUpdate();
	void ActionUpdate();
	void JumpUpdate();
	void BackFlipUpdate();
	void FalledUpdate();
	void FlyAwayUpdate();
	void DeathUpdate();
	void SlideUpdate();

	void PlayerAnimationChange(std::string _Anim);

	//HPBar
	void SetFontColor(FONT_COLOR _Color);

public:
	void ChangeHpBarFont(int _Hp);			//��Ʈ ü����
	void CreateHpBar(int _Hp, float4 _Pivot,  FONT_COLOR _Color);
	void CreateControlArrow(TeamColor _TeamColor);
	
	void MoveWeaponAngle(float _DeltaTime);
	void ChargingWeaponPower();
};

