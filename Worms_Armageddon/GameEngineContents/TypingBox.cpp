#include "TypingBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

TypingBox::TypingBox() 
{
}

TypingBox::~TypingBox() 
{
}

void TypingBox::Start()
{
	BoxRenderer_ = CreateRenderer("MouseOver_Btn.bmp", static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetScale(float4{ 931, 32 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TypingBox::Update()
{
}

