#include "TeamEditBox.h"
#include "Enums.h"
#include "TeamButton.h"

#include <GameEngine/GameEngineRenderer.h>

TeamEditBox::TeamEditBox() 
	: EditBoxRenderer_(nullptr)
	, ListBoxRenderer_(nullptr)
{
}

TeamEditBox::~TeamEditBox() 
{
}

void TeamEditBox::Start()
{
	// 버튼들 위치 초기화
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
		BtnTeam->SetPosition(DownPos_[i - 1]);
		BtnTeams_.push_back(BtnTeam);
	}

}

void TeamEditBox::Update()
{
	for (int i = 0; i < 5; i++)
	{
		bool IsSelected = BtnTeams_[i]->GetSelected();
		if (false == IsSelected)
		{
			BtnTeams_[i]->SetPosition(DownPos_[i]);
		}
		else
		{
			BtnTeams_[i]->SetPosition(UpPos_[i]);
		}
	}

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

