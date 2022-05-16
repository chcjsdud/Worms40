#include "Worms.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>

Worms::Worms()
{
}

Worms::~Worms()
{
}

void Worms::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 960 });


	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	ChangeLevel("TitleLevel");


}

void Worms::GameLoop()
{

}
void Worms::GameEnd()
{

}