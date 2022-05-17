#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class LobbyBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbyBackGround();
	~LobbyBackGround();

	// delete Function
	LobbyBackGround(const LobbyBackGround& _Other) = delete;
	LobbyBackGround(LobbyBackGround&& _Other) noexcept = delete;
	LobbyBackGround& operator=(const LobbyBackGround& _Other) = delete;
	LobbyBackGround& operator=(LobbyBackGround&& _Other) noexcept = delete;

protected:

	virtual void Start() override;
	virtual void Update() override;

private:

	GameEngineRenderer* BackGround_;

};

