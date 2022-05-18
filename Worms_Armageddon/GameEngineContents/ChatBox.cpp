#include "ChatBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ChatBox::ChatBox() 
{
}

ChatBox::~ChatBox() 
{
}

void ChatBox::Start()
{
	BoxRenderer_ = CreateRenderer(static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetImage("13268.bmp");
	BoxRenderer_->SetScale(float4{ 1248, 318});
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void ChatBox::Update()
{
}

