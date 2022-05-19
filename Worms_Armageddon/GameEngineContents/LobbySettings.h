#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class LobbySettings : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbySettings();
	~LobbySettings();

	// delete Function
	LobbySettings(const LobbySettings& _Other) = delete;
	LobbySettings(LobbySettings&& _Other) noexcept = delete;
	LobbySettings& operator=(const LobbySettings& _Other) = delete;
	LobbySettings& operator=(LobbySettings&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* BoxRenderer_;
};

