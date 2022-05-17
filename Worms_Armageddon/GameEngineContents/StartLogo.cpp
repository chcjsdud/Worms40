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
	StartLogoRenderer_ = CreateRenderer("Intro_Logo1.bmp");
}

void StartLogo::Update()
{

}

