#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class AirStrike : public WeaponMaster
{
public:
	// constrcuter destructer
	AirStrike();
	~AirStrike();

	// delete Function
	AirStrike(const AirStrike& _Other) = delete;
	AirStrike(AirStrike&& _Other) noexcept = delete;
	AirStrike& operator=(const AirStrike& _Other) = delete;
	AirStrike& operator=(AirStrike&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;
	float4 GetWeaponPosition() override;

private:
	bool IsBomb_;
	bool IsAirOff_;
};

