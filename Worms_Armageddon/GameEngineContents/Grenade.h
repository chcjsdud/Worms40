#pragma once
#include "WeaponMaster.h"

// ���� :
class PlayLevelTestMap;
class Grenade : public WeaponMaster
{
public:
	// constrcuter destructer
	Grenade();
	~Grenade();

	// delete Function
	Grenade(const Grenade& _Other) = delete;
	Grenade(Grenade&& _Other) noexcept = delete;
	Grenade& operator=(const Grenade& _Other) = delete;
	Grenade& operator=(Grenade&& _Other) noexcept = delete;

protected:
	bool WeaponUpdate() override;

protected:
	void Start() override;
	void Update() override;

};

