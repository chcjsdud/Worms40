#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// Ό³Έν :
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

protected:
	void Start() override;
	void Update() override;
};

