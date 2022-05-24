#include "TeamEditBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

// 설명 : 선택한 팀(ex. 1-UP클릭)을 TeamListBox로 올린다

//TODO:: 버튼 리스트
//TODO:: 버튼들을 담은 스크롤
//TODO:: 버튼 클릭 시 TeamListBox로 올림

TeamEditBox::TeamEditBox() 
	: BoxRenderer_(nullptr)
{
}

TeamEditBox::~TeamEditBox() 
{
}

void TeamEditBox::Start()
{
	BoxRenderer_ = CreateRenderer("6836.bmp", static_cast<int>(RenderOrder::BackGround_1));
	BoxRenderer_->SetScale(float4{ 302, 161 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TeamEditBox::Update()
{
}

