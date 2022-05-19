#pragma once
#include <GameEngine/GameEngineLevel.h>


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
	GameEngineActor* BackGround_;
	GameEngineActor* PlayersBox_;
	GameEngineActor* TeamListBox_;
	GameEngineActor* TeamEditBox_;
	GameEngineActor* ChatBox_;
	GameEngineActor* TypingBox_;
	GameEngineActor* RollingStar_;
	GameEngineActor* TerrainBox_;

	GameEngineActor* LobbySettings_;

	GameEngineActor* ReadyButton_;
	GameEngineActor* StartButton_;
	GameEngineActor* ExitButton_;

};

