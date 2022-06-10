#include "TeamHpBarList.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <numeric>
#include <algorithm>

const float SORT_SPEED = 100.0f;

// ���� �Լ�
bool CompTeamHpBar(const TeamHpBarList::TeamHpBarWithIndex& _Left, const TeamHpBarList::TeamHpBarWithIndex& _Right)
{
	return _Left.GetTeamHp() > _Right.GetTeamHp();
}

TeamHpBarList::TeamHpBarList()
{
}

TeamHpBarList::~TeamHpBarList() 
{
}

void TeamHpBarList::AddTeamHpBar(int _TeamNum, int _MemberNum)
{
	// �� �� ����
	TeamHpBar* Bar = GetLevel()->CreateActor<TeamHpBar>((int)ActorGroup::UI);
	Bar->InitTeamHpBar(_TeamNum + 1, _MemberNum);
	TeamHpBars_.push_back(Bar);
}

void TeamHpBarList::InitTeamsHpBar(int _TeamsSize)
{
	for (int i = 0; i < _TeamsSize; i++)
	{
		float Y = (_TeamsSize - i) * 18.0f;
		float4 Pos = GetPosition() - float4{ 0, Y };
		TeamHpBars_[i]->SetPosition(Pos);
		HpBarPositions_.push_back(Pos);
		SortedTeamHpBars_.push_back({ TeamHpBars_[i]->GetCurrentHp(), i});
	}

	DecreaseEndCheck_.resize(_TeamsSize, false);
}

void TeamHpBarList::SetNewTeamsHp(const std::vector<int>& _NewTeamHp)
{
	// �� ��ü������ ü���� �����̶� �پ��ٸ� Decrease�ִϸ��̼�, �ƴϸ� End
	OldTeamHp_ = NewTeamHp_;
	NewTeamHp_ = _NewTeamHp;

	SumOld_ = std::accumulate(OldTeamHp_.begin(), OldTeamHp_.end(), 0);
	SumNew_ = std::accumulate(NewTeamHp_.begin(), NewTeamHp_.end(), 0);

	if (SumOld_ != SumNew_)
	{
		ChangeState(STATE::DecreaseHP);
	}
	else
	{
		ChangeState(STATE::End);
	}
}

bool TeamHpBarList::IsAnimationEnd()
{
	// ���� End�� True
	// ���� �������̸� false
	if (State_ == STATE::End)
	{
		return true;
	}

	return false;
}

void TeamHpBarList::Start()
{
	SetPosition({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().y});
	State_ = STATE::Idle;
}

void TeamHpBarList::Update()
{
	UpdateState();
}

void TeamHpBarList::DecreaseStart()
{
	ReSetAccTime();
	for (int i = 0; i < (int)NewTeamHp_.size(); i++)
	{
		TeamHpBars_[i]->DecreaseInit(NewTeamHp_[i]);
	}
}

void TeamHpBarList::SortBarStart()
{
	// TeamHpBars_; ũ�� �� -> ũ�� ������ ���� -> HpBarPosition_���� UIMaster�̵��Լ�

	// ���� ��� ������ ü�� ������ �ε��� ����(���� �뵵)
	for (int i = 0; i < (int)SortedTeamHpBars_.size(); i++)
	{
		SortedTeamHpBars_[i].TeamHp_ = TeamHpBars_[SortedTeamHpBars_[i].Index_]->GetCurrentHp();
	}

	// �� ü�� �������� ����
	std::sort(SortedTeamHpBars_.begin(), SortedTeamHpBars_.end(), CompTeamHpBar);

	for (int i = 0; i < (int)SortedTeamHpBars_.size(); i++)
	{
		// Sorted�� ù ��° HpBar�� 1����(���� ����)
		int HpBarIndex = SortedTeamHpBars_[i].Index_;

		// HpBarPositions[0] �̵� ��ġ ����
		TeamHpBars_[HpBarIndex]->MoveSetting(TeamHpBars_[HpBarIndex]->GetPosition(), HpBarPositions_[i], SORT_SPEED);
	}

	// �̵� ����
	for (auto TeamHpBar : TeamHpBars_)
	{
		TeamHpBar->Move();
	}

}

void TeamHpBarList::DecreaseUpdate()
{
	for (int i = 0; i < (int)TeamHpBars_.size(); i++)
	{
		DecreaseEndCheck_[i] = TeamHpBars_[i]->Decrease();
	}
	
	bool IsAllEnd = false;
	int Flag = 0;
	for (auto EndCheck : DecreaseEndCheck_)
	{
		Flag += (int)EndCheck;
	}
	if ((int)DecreaseEndCheck_.size() == Flag)
	{
		IsAllEnd = true;
	}

	if (true == IsAllEnd)
	{
		if (GetAccTime() >= 2.0f)
		{
			ChangeState(STATE::SortBar);
		}
	}

}

void TeamHpBarList::SortBarUpdate()
{
	// ��� HP�� �پ�� �Ϸ� Ȯ��
	bool IsAllEnd = false;
	int Flag = 0;
	for (auto EndCheck : TeamHpBars_)
	{
		Flag += (int)EndCheck->IsMoveEnd();
	}
	if ((int)TeamHpBars_.size() == Flag)
	{
		IsAllEnd = true;
	}

	// ��� HP�� �̵� ���� ��
	if (true == IsAllEnd)
	{
		ChangeState(STATE::End);
	}
}

void TeamHpBarList::UpdateState()
{
	switch (State_)
	{
	case TeamHpBarList::STATE::Idle:
		break;
	case TeamHpBarList::STATE::DecreaseHP:
		DecreaseUpdate();
		break;
	case TeamHpBarList::STATE::SortBar:
		SortBarUpdate();
		break;
	case TeamHpBarList::STATE::End:
		break;
	default:
		break;
	}
}

void TeamHpBarList::ChangeState(STATE _State)
{
	if (State_ != _State)
	{
		switch (_State)
		{
		case TeamHpBarList::STATE::Idle:
			break;
		case TeamHpBarList::STATE::DecreaseHP:
			DecreaseStart();
			break;
		case TeamHpBarList::STATE::SortBar:
			SortBarStart();
			break;
		case TeamHpBarList::STATE::End:
			break;
		default:
			break;
		}
	}

	State_ = _State;
}