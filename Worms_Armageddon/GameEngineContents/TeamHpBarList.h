#pragma once
#include "TeamHpBar.h"
#include <GameEngine/GameEngineActor.h>
#include <vector>

// 설명 :
class TeamHpBarList : public GameEngineActor
{
public:
	bool IsAnimationEnd(); // 애니메이션 끝나면 false 반환

	void AddTeamHpBar(int _TeamNum, int _MemberNum);
	void InitTeamsHpBar(int _TeamsSize);
	void SetNewTeamsHp(const std::vector<int>& _NewTeamHp);

private:
	enum class STATE
	{
		Idle,
		DecreaseHP,			// 팀 별 체력바 줄어듬
		SortBar,			// 줄어든 체력바 정렬
		End
	};

	STATE State_;
private:
	void UpdateState();
	void ChangeState(STATE _State);

	void DecreaseStart();
	void SortBarStart();

	void DecreaseUpdate();
	void SortBarUpdate();

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

public:
	class TeamHpBarWithIndex
	{
	public:
		float GetTeamHp() const
		{
			return TeamHp_;
		}

	public:
		float TeamHp_;
		int Index_;
	};

private:
	float4 NewBarPos_;

	// 정렬시 Hp바 이동 위치
	std::vector<TeamHpBar*> TeamHpBars_;
	std::vector<TeamHpBarWithIndex> SortedTeamHpBars_;
	std::vector<float4> HpBarPositions_;
	std::vector<bool> DecreaseEndCheck_;

	std::vector<int> OldTeamHp_;
	std::vector<int> NewTeamHp_;
	int SumOld_;
	int SumNew_;

};

