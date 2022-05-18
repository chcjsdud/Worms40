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
	//������ ����ä�� �߰��� ���ҽ� ���� ����

}

