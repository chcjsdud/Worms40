#pragma once
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// ���� : 
class GameEngineImage;
class GameEngineRenderer;
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
	// ���� �߻� ����
	float4 ShotDir_;
	// TODO::���Ⱑ �߻� �Ǵ¼��� ���� ����
	bool Shot_;

	// ������ �����԰� ���ÿ� �ʱ�ȭ�� �� ����
	// static���� �����Ͽ� ��� ���Ⱑ �����ϵ��� ��
	static GameMapMaster* GameMap_;

	// �ٶ� ����
	float4 WindInfo_;

protected:
	// ���� ����
	GameEngineRenderer* WeaponRender_;

	// ����ü�� ����
	float4 BulletDir_;

	void Start() override;
	void Update() override;

	// ����ü ��ô�� �Լ� : �������� ������ ����
	void ThrowStart(float _ThrowForce);

	// ����ü ������ ���� : �߷°��� �־��ָ� ���������� ���ư�
	void BulletMove(float _Gravity);

	// ����ü �浹 �� �߻� �̺�Ʈ
	void BulletColEvent();

public:
	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}
};

