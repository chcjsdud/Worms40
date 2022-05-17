#include "LobbyLevel.h"
#include <GameEngine/GameEngineActor.h>

#include "LobbyBackGround.h"

LobbyLevel::LobbyLevel() 
{
}

LobbyLevel::~LobbyLevel() 
{
}


void LobbyLevel::Loading()
{

}

void LobbyLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<LobbyBackGround>();
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}


void LobbyLevel::Update()
{
}

