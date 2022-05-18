#pragma once
#include "PlayLevelTestMap.h"
#include "PlayLevelTestMouse.h"
#include <GameEngine/GameEngineLevel.h>
#include "LargeCloud.h"

// Ό³Έν :
class Baz;
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
	PlayLevelTestMouse* PlayLevelTestMouse_;
	LargeCloud* LargeCloudActor_;
	Baz* BazTset_;
	Player* Player_;


private:
	void CreateTestBullet();
};

