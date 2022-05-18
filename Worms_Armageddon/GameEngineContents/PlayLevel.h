#pragma once
#include "PlayLevelTestMap.h"
#include <GameEngine/GameEngineLevel.h>
#include "LargeCloud.h"
#include "Cursor.h"

// Ό³Έν :
class WeaponMaster;
class Player;
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
	PlayLevelTestMap* PlayLevelTestMap_;
	LargeCloud* LargeCloudActor_;
	WeaponMaster* WeaponTset_;
	Player* Player_;
	Cursor* Mouse_;


private:
	void CreateTestBullet();
};

