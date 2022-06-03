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

private: 
	// ������ ��ǥ ��ǥ
	float4 TargetPos_;
	// ���Ⱑ �߻� �Ǵ¼��� ���� ����
	bool Shot_;
	bool IsShot_;
	// �����ϴ� ���� ���� ����
	bool IsDrop_;

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

	void Start() override;
	void Update() override;

	// ����ü ��ô�� �Լ� : �������� ������ ����
	void ThrowStart(float _ThrowForce);
	// ���ݱ� ��� : ���ݱⰡ ��� �������� �̵����� ����
	void AirStart(float4 _FlyDir);

	// ����ü ������ ���� : �߷°��� �־��ָ� ���������� ���ư�
	void BulletMove(float _Gravity);
	// ���� ��ź ���� : ��� ��ź�� �������� ����
	void Bombing(WeaponState _Bomb);

	// ����ü �浹 �� �߻� �̺�Ʈ
	void BulletColEvent();

public:
	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}
};

