#include "FadeIn.h"
#include "GameEngineBase//GameEngineWindow.h"


FadeIn::FadeIn() 
	:
	Alpha_(255.f),
	FadeRenderer_(nullptr)
{
}

FadeIn::~FadeIn() 
{
}

void FadeIn::Start()
{
	FadeRenderer_ = CreateRenderer("Fade_Black.bmp");
	FadeRenderer_->SetScale({GameEngineWindow::GetInst().GetScale()});
	FadeRenderer_->SetAlpha(255);
	this->SetPosition({ GameEngineWindow::GetInst().GetScale().Half() });

}

void FadeIn::Update()
{

	Alpha_-= (3.f + (GameEngineTime::GetInst()->GetDeltaTime()));
	FadeRenderer_->SetAlpha(static_cast<unsigned int>(Alpha_));

	if (Alpha_ <= 0)
	{
		this->Death();
	}
	
}

