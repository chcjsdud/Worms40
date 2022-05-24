#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class PlayersBox : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayersBox();
	~PlayersBox();

	// delete Function
	PlayersBox(const PlayersBox& _Other) = delete;
	PlayersBox(PlayersBox&& _Other) noexcept = delete;
	PlayersBox& operator=(const PlayersBox& _Other) = delete;
	PlayersBox& operator=(PlayersBox&& _Other) noexcept = delete;

public:
	void BulbOn();
	void BulbOff();


protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* BoxRenderer_;
	GameEngineRenderer* BulbRenderer_;
	
};

