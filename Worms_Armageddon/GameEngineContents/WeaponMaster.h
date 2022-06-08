#pragma once
#include "Enums.h"
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

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

	inline void SetShotAngle(float4 _ShotAngle)
	{
		ShotAngle_ = _ShotAngle;
	}

	inline void SetShotPower(float _ShotPower)
	{
		ShotPower_ = _ShotPower;
	}

private: 
	// ������ ��ǥ ��ǥ
	float4 TargetPos_;
	// ���Ⱑ �߻� �Ǵ¼��� ���� ����
	bool Shot_;
	bool IsShot_;
	// �����ϴ� ���� ���� ����
	bool IsDrop_;
	// �ٿ ����ü�� ������ ���� ȸ����
	float BounceRotate_;
	bool IsBomb_;

	// ������ �����԰� ���ÿ� �ʱ�ȭ�� �� ����
	// static���� �����Ͽ� ��� ���Ⱑ �����ϵ��� ��
	static GameMapMaster* GameMap_;

	// �ٶ� ���� ����
	float4 WindInfo_;
	// ����ü�� �ڽ� ����ü�� ������ Ƚ��
	int BombCnt_;

	// ����ü ���� : � ���� �������� ����, ���Ͻð� ����
	void Drop(WeaponState _Drop, float _Sec = 0);

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

	// ī�޶� ������ ������ ��ġ
	// �⺻�����δ� GetPosition(), ���ݱ���� ����ü�� ������쿡�� Ư���ϰ� ����
	static float4 WeaponCameraPos_;

	static bool WeaponStaticReturn_;

	void Start() override;
	void Update() override;

	// ����ü ��ô�� �Լ� : �������� ������ ����
	void ThrowStart(float _ThrowForce);
	// ���ݱ� ��� : ���ݱⰡ ��� �������� ����
	void AirStart(float4 _AirSpawn);

	// ����ü ������ ���� : �߷°��� �־��ָ� ���������� ���ư�
	void BulletMove(float _Gravity, bool _IsWind);
	// ���� ��ź ���� : ��� ��ź�� �������� ����
	bool Bombing(WeaponState _Bomb);

	// ����ü �浹 �� �߻� �̺�Ʈ
	bool BulletColEvent();
	// ���� (���� �İ� ���� ����Ʈ����� ����ü ����)
	void Explosion();

public:
	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}
};

