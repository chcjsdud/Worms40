#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// 설명 : 
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

	virtual bool WeaponUpdate() 
	{ 
		return true;
	}


/// <summary>
private: // 임시용->추후 정리 할 때 기능들 넣을 예정
	float4 WeaponDir_;
	bool IsThrow_;
/// </summary>

protected:
	void Start() override;
	void Update() override;

	inline float4 GetWeaponDir() const
	{
		return WeaponDir_;
	}

public:
	void SetWeaponDir(float4 _WeaponDir)
	{
		WeaponDir_ = _WeaponDir;
	}
};

