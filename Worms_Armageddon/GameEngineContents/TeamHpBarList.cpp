#include "TeamHpBarList.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>

TeamHpBarList::TeamHpBarList() 
{
}

TeamHpBarList::~TeamHpBarList() 
{
}

void TeamHpBarList::InitTeamSize(int _TeamNum)
{
	// 팀 개수만큼 바 생성
	for (int i = 0; i < _TeamNum; i++)
	{
		float Y = (_TeamNum - i) * 17.0f;
		float4 Pos = GetPosition() - float4{ 0, Y };
		HpBarPositions_.push_back(Pos);
	}

	for (int i = 0; i < _TeamNum; i++)
	{
		TeamHpBar* Bar = GetLevel()->CreateActor<TeamHpBar>((int)ActorGroup::UI);
		Bar->SetPosition(HpBarPositions_[i]);
		Bar->InitTeamHpBar(i+1);
	}
}

void TeamHpBarList::SetTeamsHpInfo(std::vector<int>* _TeamsHp)
{

}

void TeamHpBarList::Start()
{
	SetPosition({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().y});
	InitTeamSize(3);

}

void TeamHpBarList::Update()
{
}
