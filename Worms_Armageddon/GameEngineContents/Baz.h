#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class GameEngineRenderer;
class PlayLevelTestMap;
class Baz : public WeaponMaster
{
public:
	// constrcuter destructer
	Baz();
	~Baz();

	// delete Function
	Baz(const Baz& _Other) = delete;
	Baz(Baz&& _Other) noexcept = delete;
	Baz& operator=(const Baz& _Other) = delete;
	Baz& operator=(Baz&& _Other) noexcept = delete;

	bool WeaponUpdate() override;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
	float4 Baz_WindSpeed;

private:
	GameEngineRenderer* WeaponRender_;
	float4 BazDir_;
	bool IsStart_;
	PlayLevelTestMap* MapRender_;

public:
	inline void SetWindSpeed(float4 _windspeed)
	{
		Baz_WindSpeed = _windspeed;
	}
};

