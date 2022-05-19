#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// ���� : 
class GameEngineImage;
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


private: 
	// ���� �߻� ����
	float4 WeaponDir_;
	// TODO::���Ⱑ �߻� �Ǵ¼��� ���� ����(�ӽ�)
	bool IsThrow_;
	// �浹�� �� �̹���
	GameEngineImage* ColMapImage_;


protected:
	void Start() override;
	void Update() override;

	inline float4 GetWeaponDir() const
	{
		return WeaponDir_;
	}

	inline GameEngineImage* GetColMapImage()
	{
		return ColMapImage_;
	}

public:
	inline void SetWeaponDir(float4 _WeaponDir)
	{
		WeaponDir_ = _WeaponDir;
	}

	inline void SetColMapImage(GameEngineImage* _ColMapImage)
	{
		ColMapImage_ = _ColMapImage;
	}
};

