#pragma once
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// 설명 : 
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
	// 무기 발사 방향
	float4 ShotDir_;
	// TODO::무기가 발사 되는순간 최초 실행
	bool Shot_;

	// 레벨이 시작함과 동시에 초기화될 맵 정보
	// static으로 설정하여 모든 무기가 공유하도록 함
	static GameMapMaster* GameMap_;

	// 바람 정보
	float4 WindInfo_;

protected:
	// 무기 랜더
	GameEngineRenderer* WeaponRender_;

	// 투사체의 방향
	float4 BulletDir_;

	void Start() override;
	void Update() override;

	// 투사체 투척용 함수 : 포스값의 강도로 날림
	void ThrowStart(float _ThrowForce);

	// 투사체 움직임 연산 : 중력값만 넣어주면 포물선으로 날아감
	void BulletMove(float _Gravity);

	// 투사체 충돌 시 발생 이벤트
	void BulletColEvent();

public:
	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}
};

