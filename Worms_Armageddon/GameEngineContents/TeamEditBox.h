#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <list>

// Ό³Έν :
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

	inline int GetSelectedTeamNum()
	{
		return static_cast<int>(SelectedTeams_.size());
	}

	std::list<TeamButton*>& GetSelectedTeams()
	{
		return SelectedTeams_;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;
private:
	GameEngineRenderer* EditBoxRenderer_;
	GameEngineRenderer* ListBoxRenderer_;

	std::vector<float4> UpPos_;
	std::vector<float4> DownPos_;

	std::list<TeamButton*> UnSelectedTeams_;
	std::list<TeamButton*> SelectedTeams_;

private:
	void InitButtonPos();
	void CheckSelectedTeam();
	void ShowTeamsButton();
};

