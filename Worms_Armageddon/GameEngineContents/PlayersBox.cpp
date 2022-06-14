#include "PlayersBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

PlayersBox::PlayersBox() 
	: BoxRenderer_(nullptr)
	, BulbRenderer_(nullptr)
{
}

PlayersBox::~PlayersBox() 
{
}

void PlayersBox::BulbOn()
{
	BulbRenderer_->SetImage("ON.bmp");
	BulbRenderer_->SetScale(BulbRenderer_->GetScale() * 2);
	BulbRenderer_->SetPivot({ 23, 17 });
}

void PlayersBox::BulbOff()
{
	BulbRenderer_->SetImage("OFF.bmp");
	BulbRenderer_->SetScale(BulbRenderer_->GetScale() * 2);
	BulbRenderer_->SetPivot({ 23, 17 });
}

void PlayersBox::Start()
{
	BoxRenderer_ = CreateRenderer("4459.bmp", static_cast<int>(RenderOrder::BackGround_1));
	BoxRenderer_->SetScale(float4{ 222, 258 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

	// 국기 + 플레이어 닉네임
	GameEngineRenderer* PlayerBoxRenderer = CreateRenderer("PlayerBox.bmp", static_cast<int>(RenderOrder::UI));
	PlayerBoxRenderer->SetScale(PlayerBoxRenderer->GetScale()*2);
	PlayerBoxRenderer->SetPivot({ 132, 19 });

	// 전구
	BulbRenderer_ = CreateRenderer("OFF.bmp", static_cast<int>(RenderOrder::UI));
	BulbRenderer_->SetScale(BulbRenderer_->GetScale() * 2);
	BulbRenderer_->SetPivot({ 23, 17 });
}

void PlayersBox::Update()
{
}


