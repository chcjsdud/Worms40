#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class SuperSheep : public WeaponMaster
{
public:
	// constrcuter destructer
	SuperSheep();
	~SuperSheep();

	// delete Function
	SuperSheep(const SuperSheep& _Other) = delete;
	SuperSheep(SuperSheep&& _Other) noexcept = delete;
	SuperSheep& operator=(const SuperSheep& _Other) = delete;
	SuperSheep& operator=(SuperSheep&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
	bool WeaponUpdate() override;

private:
	bool IsSuper_;
	int ModeCnt_;
	float SpDegree_;
	float4 SheepFlyDir_;

	void CycleFly();
};

