#pragma once
#include "WeaponMaster.h"
#include "GrenadeTimerBox.h"

// Ό³Έν :
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
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;

private:
	GrenadeTimerBox* GrenadeTimerBox_;
	

public:
	void CreateGrenadeTimerBox(TeamColor _Color) override;

};

