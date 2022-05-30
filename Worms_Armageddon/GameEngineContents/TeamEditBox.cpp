#include "TeamEditBox.h"
#include "Enums.h"
#include "TeamButton.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <algorithm>

TeamEditBox::TeamEditBox() 
	: EditBoxRenderer_(nullptr)
	, ListBoxRenderer_(nullptr)
{
}

TeamEditBox::~TeamEditBox() 
{
}

bool CompButton(TeamButton* _Left, TeamButton* _Right)
{
	return _Left->GetButtonIndex() < _Right->GetButtonIndex();
}

void TeamEditBox::Start()
{
	// ��ư�� ��ġ �ʱ�ȭ
	InitButtonPos();

	ListBoxRenderer_ = CreateRenderer("6868.bmp", static_cast<int>(RenderOrder::BackGround_1));
	ListBoxRenderer_->SetScale(float4{ 302, 230 });
	ListBoxRenderer_->SetPivot(ListBoxRenderer_->GetScale().Half());

	EditBoxRenderer_ = CreateRenderer("6836.bmp", static_cast<int>(RenderOrder::BackGround_1));
	EditBoxRenderer_->SetScale(float4{ 302, 161 });
	EditBoxRenderer_->SetPivot(EditBoxRenderer_->GetScale().Half() + float4{ 0, 280.0f });


	for (int i = 1; i < 6; i++)
	{
		GameEngineActor* Ptr = GetLevel()->CreateActor<TeamButton>(static_cast<int>(ActorGroup::UI));
		TeamButton* BtnTeam = dynamic_cast<TeamButton*>(Ptr);
		BtnTeam->SetButton(i);
		BtnTeam->SetAllButtonPosition(DownPos_[i - 1]);
		UnSelectedTeams_.push_back(BtnTeam);
	}

}

void TeamEditBox::Update()
{
	CheckSelectedTeam();

	ShowTeamsButton();
}

void TeamEditBox::InitButtonPos()
{
	for (int i = 0; i < 5; i++)
	{
		UpPos_.push_back(float4{ 265, static_cast<float>(20 + (i * 30)) });
	}

	for (int i = 0; i < 5; i++)
	{
		DownPos_.push_back(float4{ 265, static_cast<float>(300 + (i * 30)) });
	}
}

void TeamEditBox::CheckSelectedTeam()
{
	// Unselected�� ���� �Ȱ� �ø���
	// Selected�� ��ư �ٽ� Ŭ���ϸ� ������

	for (auto& Button : UnSelectedTeams_)
	{
		if (true == Button->GetSelected())
		{
			SelectedTeams_.push_back(Button);
			UnSelectedTeams_.remove(Button);
			return;
		}
	}

	for (auto& Button : SelectedTeams_)
	{
		if (false == Button->GetSelected())
		{
			//UnselectedTeams�� GetButtonIndexȮ���Ͽ� ����
			UnSelectedTeams_.push_back(Button);
			SelectedTeams_.remove(Button);
			UnSelectedTeams_.sort(CompButton);
			return;
		}
	}

}

void TeamEditBox::ShowTeamsButton()
{
	// selected
	{
		std::list<TeamButton*>::iterator StartIt = SelectedTeams_.begin();
		std::list<TeamButton*>::iterator EndIt = SelectedTeams_.end();

		int PosIdx = 0;
		for (; StartIt != EndIt; ++StartIt)
		{
			(*StartIt)->SetAllButtonPosition(UpPos_[PosIdx++]);
		}
	}


	// TODO:: unselected ����

	{
		std::list<TeamButton*>::iterator StartIt = UnSelectedTeams_.begin();
		std::list<TeamButton*>::iterator EndIt = UnSelectedTeams_.end();

		int PosIdx = 0;
		for (; StartIt != EndIt; ++StartIt)
		{
			(*StartIt)->SetAllButtonPosition(DownPos_[PosIdx++]);
		}
	}

}
