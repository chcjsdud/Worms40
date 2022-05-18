#include "TeamEditBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

TeamEditBox::TeamEditBox() 
{
}

TeamEditBox::~TeamEditBox() 
{
}

void TeamEditBox::Start()
{
	BoxRenderer_ = CreateRenderer("6836.bmp", static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetScale(float4{ 302, 161 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TeamEditBox::Update()
{
}

