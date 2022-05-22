#pragma once
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// ���� : 
class GameEngineImage;
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
	float4 WeaponDir_;
	// TODO::���Ⱑ �߻� �Ǵ¼��� ���� ����(�ӽ�)
	bool IsThrow_;

	// ������ �����԰� ���ÿ� �ʱ�ȭ�� �� ����
	// static���� �����Ͽ� ��� ���Ⱑ �����ϵ��� ��
	static GameMapMaster* GameMap_;

	static GameEngineImage* PixelTestImage_;
	GameEngineRenderer* MapPixelTestRender_;

protected:
	void Start() override;
	void Update() override;

	inline float4 GetWeaponDir() const
	{
		return WeaponDir_;
	}

public:
	inline void SetWeaponDir(float4 _WeaponDir)
	{
		WeaponDir_ = _WeaponDir;
	}
};

