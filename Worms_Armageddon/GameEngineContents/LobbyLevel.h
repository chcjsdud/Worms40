#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Font.h"
#include "LobbyShootingStar.h"
#include "ChattingBox.h"
#include "ChatBox.h"

// Ό³Έν :
class GameEngineActor;
class LobbyLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LobbyLevel();
	~LobbyLevel();

	// delete Function
	LobbyLevel(const LobbyLevel& _Other) = delete;
	LobbyLevel(LobbyLevel&& _Other) noexcept = delete;
	LobbyLevel& operator=(const LobbyLevel& _Other) = delete;
	LobbyLevel& operator=(LobbyLevel&& _Other) noexcept = delete;

protected:
	void LevelChangeStart(GameEngineLevel* _PrevLevel);
	void LevelChangeEnd(GameEngineLevel* _NextLevel);
	void Loading() override;
	void Update() override;

private:
	void PlayerReadyCheck();

private:
	GameEngineActor* BackGround_;
	GameEngineActor* PlayersBox_;
	GameEngineActor* TeamListBox_;
	GameEngineActor* TeamEditBox_;

	GameEngineActor* TypingBox_;
	GameEngineActor* TerrainBox_;

	GameEngineActor* LobbySettings_;

	GameEngineActor* ReadyButton_;
	GameEngineActor* StartButton_;
	GameEngineActor* ExitButton_;

	ChatBox* ChatBox_;

	LobbyShootingStar* LobbyShootingStar_;

	ChattingBox* ChattingBox_;

	GameEngineSoundPlayer SoundPlayer_;
};

