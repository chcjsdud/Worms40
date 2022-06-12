#pragma once
#include "WeaponMaster.h"

// 설명 :
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

	inline void SetBombCount(int _BombCount)
	{
		BombCount_ = _BombCount;
	}

	inline bool GetAirBombExplodEnd()
	{
		return AirBombExplodEnd_;
	}

	void ResgistBomb();
protected:
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;

private: 
	// 내가 몇번째 폭탄인가
	int BombCount_;
	bool AirBombExplodEnd_;
};

