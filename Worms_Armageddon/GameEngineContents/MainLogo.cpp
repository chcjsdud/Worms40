#include "MainLogo.h"
#include <GameEngine/GameEngineRenderer.h>

MainLogo::MainLogo()
	:
	MainLogoRenderer_(nullptr)
{
}

MainLogo::~MainLogo()
{
}

void MainLogo::Start()
{
	MainLogoRenderer_ = CreateRenderer("Title_Logo.bmp");
}

void MainLogo::Update()
{

	int a = 0;

}

