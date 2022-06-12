#pragma once
#include "WeaponMaster.h"

// ���� :
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
	// ���� ���° ��ź�ΰ�
	int BombCount_;
	bool AirBombExplodEnd_;
};

