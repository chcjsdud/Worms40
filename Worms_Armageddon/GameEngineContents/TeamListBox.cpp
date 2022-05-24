#include "TeamListBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

// 설명 : TeamEditBox에서에서 선택한 팀을 보여준다

//TODO:: TeamEditBox에서 선택한 버튼 올림
//TODO:: 올려진 팀, 팀원 수 와 색 설정 기능

TeamListBox::TeamListBox() 
	: BoxRenderer_(nullptr)
{
}

TeamListBox::~TeamListBox() 
{
}

void TeamListBox::Start()
{
	BoxRenderer_ = CreateRenderer("6868.bmp", static_cast<int>(RenderOrder::BackGround_1));
	BoxRenderer_->SetScale(float4{ 302, 230 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TeamListBox::Update()
{
}

