#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineRenderer;
class TeamButton;
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
	GameEngineRenderer* EditBoxRenderer_;
	GameEngineRenderer* ListBoxRenderer_;

	std::vector<TeamButton*> BtnTeams_;
	std::vector<float4> UpPos_;
	std::vector<float4> DownPos_;



private:
	void InitButtonPos();

};

