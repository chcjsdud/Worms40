#include "ReadyButton.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ReadyButton::ReadyButton() 
	: IsPlayerReady_(false)
	, IsMouseIn_(false)
	, ButtonRenderer_(nullptr)
{
}

ReadyButton::~ReadyButton() 
{
}

void ReadyButton::Start()
{
	ButtonRenderer_ = CreateRenderer("Btn_NotReady_Idle.bmp", (int)RenderOrder::UI);
	ButtonRenderer_->SetScale({ 217, 154 });
	ButtonRenderer_->SetPivot(ButtonRenderer_->GetScale().Half());

}

void ReadyButton::Update()
{
}

void ReadyButton::ButtonBorder()
{
	if (false == IsMouseIn_)
	{
		return;
	}


}

