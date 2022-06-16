#pragma once
#include "Enums.h"
#include "GameMapMaster.h"
#include "TimerBox.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngineBase/GameEngineSound.h>

// ���� : 
class GameEngineImage;
class GameEngineRenderer;
class PixelCollision;
class WeaponMaster :public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponMaster();
	~WeaponMaster();

	// delete Function
	WeaponMaster(const WeaponMaster& _Other) = delete;
	WeaponMaster(WeaponMaster&& _Other) noexcept = delete;
	WeaponMaster& operator=(const WeaponMaster& _Other) = delete;
	WeaponMaster& operator=(WeaponMaster&& _Other) noexcept = delete;

	void CreateTimerBox(TeamColor _Color);


	virtual bool WeaponUpdate() 
	{ 
		return true;
	}

	static inline void SetGameMap(GameMapMaster* _GameMap)
	{
		GameMap_ = _GameMap;
	}

	static inline GameMapMaster* GetGameMap()
	{
		return GameMap_;
	}

	virtual float4 GetWeaponPosition()
	{
		return GetPosition();
	}

	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}

	inline void SetShotAngle(float4 _ShotAngle)
	{
		ShotAngle_ = _ShotAngle;
	}

	inline void SetShotPower(float _ShotPower)
	{
		ShotPower_ = _ShotPower;
	}

	inline bool GetExplodEndFlg() const
	{
		return IsExplodEnd_;
	}

	inline TimerBox* GetTimerBox() const
	{
		return TimerBox_;
	}

	inline void SetTeamColor(TeamColor _Color)
	{
		MyTeamColor_ = _Color;
	}

private: 
	// ������ ��ǥ ��ǥ
	float4 TargetPos_;
	// ���Ⱑ �߻� �Ǵ¼��� ���� ����
	bool IsShot_;
	// �����ϴ� ���� ���� ����
	bool IsDrop_;
	// ����ü�� �ڽ� ����ü�� ������ Ƚ��
	int BombCnt_;
	// �ٿ ����ü�� ������ ���� ȸ����
	float BounceRotate_;
	// 
	bool IsBomb_;
	// ������ ������ ������ �÷���
	bool IsExplodEnd_;
	//
	float JumpTime_;

	// ����
	GameEngineSoundPlayer SoundPlayer_Explode_;


	// ���� ����ü ������ ��
	float4 AnimalMoveDir_;
	float Speed_;
	float FallLength_;
	float FallSpeed_;
	bool IsJump_;
	bool IsJumpCol_;
	float JumpSpeed_;
	float4 JumpMoveDir_;


	// ������ �����԰� ���ÿ� �ʱ�ȭ�� �� ����
	// static���� �����Ͽ� ��� ���Ⱑ �����ϵ��� ��
	static GameMapMaster* GameMap_;
	// �ٶ� ���� ����
	float4 WindDirInfo_;
	

	// ����ü ���� : � ���� �������� ����, ���Ͻð� ����
	void Drop(WeaponState _Drop, float _Sec = 0);
	//
	void AnimalFall();
	//
	void AnimalJump();

protected:
	// ���� ����
	GameEngineRenderer* WeaponRender_;
	//ƨ��� �������� �ƴ��� üũ���ִ� ����
	bool IsBounce_;
	// ���� �߻� ����
	float4 ShotDir_;
	PixelCollision* PixelCol_;
	// ����ü�� ����
	float4 BulletDir_;
	// ���� �߻簢��
	float4 ShotAngle_;
	// ���� �߻� ��
	float ShotPower_;
	// ���� �ð�
	float SelfDestructSec_;
	//Ÿ�̸� �ڽ�
	TimerBox* TimerBox_;
	// ���� �� ���� ����
	TeamColor MyTeamColor_;
	// 
	bool IsTimerCreate_;


	// ī�޶� ������ ������ ��ġ
	// �⺻�����δ� GetPosition(), ���ݱ���� ����ü�� ������쿡�� Ư���ϰ� ����
	static float4 WeaponCameraPos_;
	//
	static bool WeaponStaticReturn_;


	void Start() override;
	void Update() override;


	// ����ü ��ô�� �Լ� : �������� ������ ����
	void ThrowStart(float _ThrowForce);
	// ���ݱ� ��� : ���ݱⰡ ��� �������� ����
	void AirStart(float4 _AirSpawn);
	// ��ǥ ��ǥ ����
	void TargetCursor();

	// ����ü ������ ���� : �߷°��� �־��ָ� ���������� ���ư�, �ٶ� ���� ������
	void BulletMove(float _Gravity, bool _IsWind);
	// ���� ��ź ���� : ��� ��ź�� �������� ����
	bool Bombing(WeaponState _Bomb);
	//
	void AnimalMoveCheck(float4 _Dir);
	// ���� ������ ������
	void AnimalMove(WeaponState _Animal = WeaponState::None);

	// ����ü �浹 �� �߻� �̺�Ʈ
	bool BulletColEvent();
	// ���� (���� �İ� ���� ����Ʈ����� ����ü ����)
	void Explosion();

	// ����ü �ٴ� ���� �Ѿ���� üũ
	bool IsBulletOutofBound();

public:

	// ������ ��ź�� ����
	static GameEngineActor* AirBombArr_[5];
	static GameEngineActor* ExplodeWeapon_;
	inline GameEngineActor* GetAirBomb_(int _Num)
	{
		if (AirBombArr_[_Num] != nullptr)
		{
			return AirBombArr_[_Num];
		}

		return nullptr;
	}
};

