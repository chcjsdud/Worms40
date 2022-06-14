#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>

// 설명 :
class ChargeBlob : public GameEngineActor
{
public:
	void SetChargePower(float _ChargePower, float4 _PlayerPos, float4 _ShootVec);
	
	// Update플래그와 사운드 함께 다룸
	void DeActivate();

public:
	// constrcuter destructer
	ChargeBlob();
	~ChargeBlob();

	// delete Function
	ChargeBlob(const ChargeBlob& _Other) = delete;
	ChargeBlob(ChargeBlob&& _Other) noexcept = delete;
	ChargeBlob& operator=(const ChargeBlob& _Other) = delete;
	ChargeBlob& operator=(ChargeBlob&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::vector<GameEngineRenderer*> Blobs_;
	
	GameEngineSoundPlayer SoundPlayer_;
	bool IsSoundPlay_;
};

