#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
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
	void Loading() override;
	void Update() override;
private:

};

