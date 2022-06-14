#pragma once
#include "WeaponMaster.h"

// ���� :
class GrenadeTimerBox;
class Sheep : public WeaponMaster
{
public:
	// constrcuter destructer
	Sheep();
	~Sheep();

	// delete Function
	Sheep(const Sheep& _Other) = delete;
	Sheep(Sheep&& _Other) noexcept = delete;
	Sheep& operator=(const Sheep& _Other) = delete;
	Sheep& operator=(Sheep&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;
	void CreateGrenadeTimerBox(TeamColor _Color) override;

private:
	GrenadeTimerBox* GrenadeTimerBox_;
};

