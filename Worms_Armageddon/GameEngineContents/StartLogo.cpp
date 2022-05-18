#include "StartLogo.h"
#include <GameEngine/GameEngineRenderer.h>


StartLogo::StartLogo()
	:
	StartLogoRenderer_(nullptr)
{
}

StartLogo::~StartLogo()
{
}

void StartLogo::Start()
{
	StartLogoRenderer_ = CreateRenderer("Intro_LogoAlpha.bmp");
	StartLogoRenderer_->SetAlpha(255);
}

void StartLogo::Update()
{
	//집가서 알파채널 추가한 리소스 수정 예정

}

