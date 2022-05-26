#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "LargeCloud.h"
#include "Cursor.h"
#include "WindGauge.h"
#include "SmallCloud.h"
#include "Water.h"

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

	Water* WaterActor_;
	WeaponMaster* WeaponMaster_;
	Cursor* Mouse_;
	WindGauge* WindGaugeActor_;

	float4 WindDir_;
	float WindSpeed_;

	Player* Player_[PLAYER_MAX_TEAM][PLAYER_MAX_NUMBER];
	std::map<TeamColor, int> PlayerColorTeamSetting_;

	std::list<std::list<Player*>>::iterator AllPlayerIter_;
	std::list<std::list<Player*>> AllPlayer_;
	std::list<std::list<Player*>> PlayQueue_;
	std::list<Player*> DeathList_;
	Player* TargetPlayer_;

	LevelFSM LevelPhase_;
private:
	void CreateTestBullet();
	void SetWindUI(int _WindDir);

public:
	float4 GetWindDir()
	{
		return WindDir_;
	}
};

