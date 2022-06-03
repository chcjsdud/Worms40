#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class AirBomb : public WeaponMaster
{
public:
	// constrcuter destructer
	AirBomb();
	~AirBomb();

	// delete Function
	AirBomb(const AirBomb& _Other) = delete;
	AirBomb(AirBomb&& _Other) noexcept = delete;
	AirBomb& operator=(const AirBomb& _Other) = delete;
	AirBomb& operator=(AirBomb&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;

};

