#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "LargeCloud.h"
#include "Cursor.h"
#include "WindGauge.h"
#include "SmallCloud.h"

// Ό³Έν :
class WeaponMaster;
class GameMapMaster;
class Player;
class GameEngineRenderer;
class GameEngineImage;
class PlayLevel	:public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameMapMaster* GameMapInfo_;
	LargeCloud* LargeCloudActor_;
	SmallCloud* SmallCloudActor_;


	WeaponMaster* WeaponTset_;
	Player* Player_;
	Cursor* Mouse_;
	WindGauge* WindGaugeActor_;

	float4 WindDir_;
	float WindSpeed_;



private:
	void CreateTestBullet();
	void SetWindUI(int _WindDir);

public:
	float4 GetWindDir()
	{
		return WindDir_;
	}
};

