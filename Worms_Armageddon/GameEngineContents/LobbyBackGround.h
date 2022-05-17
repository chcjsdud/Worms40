#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
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

private:
	void Start() override;
	void Update() override;

	GameEngineRenderer* BackGround_;

};

