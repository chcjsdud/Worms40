#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <GameEngineBase/GameEngineSound.h>

// ���� :
class ChargeBlob : public GameEngineActor
{
public:
	void SetChargePower(float _ChargePower, float4 _PlayerPos, float4 _ShootVec);
	
	// Update�÷��׿� ���� �Բ� �ٷ�
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

