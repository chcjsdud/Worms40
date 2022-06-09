#pragma once
#include "TeamHpBar.h"
#include <GameEngine/GameEngineActor.h>
#include <vector>

// ���� :
class TeamHpBarList : public GameEngineActor
{
public:
	bool IsAnimationEnd(); // �ִϸ��̼� ������ false ��ȯ

	void AddTeamHpBar(int _TeamNum, int _MemberNum);
	void InitTeamsHpBar(int _TeamsSize);
	void SetNewTeamsHp(const std::vector<int>& _NewTeamHp);

private:
	enum class STATE
	{
		Idle,
		DecreaseHP,			// �� �� ü�¹� �پ��
		SortBar,			// �پ�� ü�¹� ����
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

	// ���Ľ� Hp�� �̵� ��ġ
	std::vector<TeamHpBar*> TeamHpBars_;
	std::vector<TeamHpBarWithIndex> SortedTeamHpBars_;
	std::vector<float4> HpBarPositions_;
	std::vector<bool> DecreaseEndCheck_;

	std::vector<int> OldTeamHp_;
	std::vector<int> NewTeamHp_;
	int SumOld_;
	int SumNew_;

};

