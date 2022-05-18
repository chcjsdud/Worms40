#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class TeamListBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TeamListBox();
	~TeamListBox();

	// delete Function
	TeamListBox(const TeamListBox& _Other) = delete;
	TeamListBox(TeamListBox&& _Other) noexcept = delete;
	TeamListBox& operator=(const TeamListBox& _Other) = delete;
	TeamListBox& operator=(TeamListBox&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
private:
	GameEngineRenderer* BoxRenderer_;
};

