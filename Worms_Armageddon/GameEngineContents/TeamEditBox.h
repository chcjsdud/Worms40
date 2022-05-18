#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class TeamEditBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TeamEditBox();
	~TeamEditBox();

	// delete Function
	TeamEditBox(const TeamEditBox& _Other) = delete;
	TeamEditBox(TeamEditBox&& _Other) noexcept = delete;
	TeamEditBox& operator=(const TeamEditBox& _Other) = delete;
	TeamEditBox& operator=(TeamEditBox&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
private:
	GameEngineRenderer* BoxRenderer_;

};

