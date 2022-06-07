#pragma once
#include "TeamHpBar.h"
#include <GameEngine/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class TeamHpBarList : public GameEngineActor
{
private:
	enum class STATE
	{
		Decreasing,
		End
	};

public:
	void InitTeamSize(int _TeamNum);
	void SetTeamsHpInfo(std::vector<int>* _TeamsHp);

public:
	// constrcuter destructer
	TeamHpBarList();
	~TeamHpBarList();

	// delete Function
	TeamHpBarList(const TeamHpBarList& _Other) = delete;
	TeamHpBarList(TeamHpBarList&& _Other) noexcept = delete;
	TeamHpBarList& operator=(const TeamHpBarList& _Other) = delete;
	TeamHpBarList& operator=(TeamHpBarList&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	STATE State_;

	std::vector<float4> HpBarPositions_;
};

