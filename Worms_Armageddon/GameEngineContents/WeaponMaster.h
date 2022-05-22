#pragma once
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// 설명 : 
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
	// 무기 발사 방향
	float4 WeaponDir_;
	// TODO::무기가 발사 되는순간 최초 실행(임시)
	bool IsThrow_;

	// 레벨이 시작함과 동시에 초기화될 맵 정보
	// static으로 설정하여 모든 무기가 공유하도록 함
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

