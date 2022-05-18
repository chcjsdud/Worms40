#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	GameEngineRenderer* Renderer_;

};
