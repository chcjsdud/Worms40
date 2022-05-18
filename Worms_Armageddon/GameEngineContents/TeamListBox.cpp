#include "TeamListBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

TeamListBox::TeamListBox() 
{
}

TeamListBox::~TeamListBox() 
{
}

void TeamListBox::Start()
{
	BoxRenderer_ = CreateRenderer("6868.bmp", static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetScale(float4{ 302, 230 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TeamListBox::Update()
{
}

