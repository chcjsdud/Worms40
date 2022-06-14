#pragma once
#include "WeaponMaster.h"

// 설명 :
class TimerBox;
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
	bool WeaponUpdate() override;
	void CreateTimerBox(TeamColor _Color) override;


private:
	bool IsSuper_;
	int ModeCnt_;
	float SpDegree_;
	float4 SheepFlyDir_;
	TimerBox* TimerBox_;

	// 회전 애니메이션 랜더 (0= 반시계, 1= 시계)
	void CycleFly(int _CycleDir);
};

