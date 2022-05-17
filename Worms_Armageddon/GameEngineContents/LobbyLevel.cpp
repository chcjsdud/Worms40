#include "LobbyLevel.h"
#include <GameEngine/GameEngineActor.h>

#include "LobbyBackGround.h"
#include "Enums.h"

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
	CreateActor<LobbyBackGround>(static_cast<int>(ActorGroup::UI));
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}


void LobbyLevel::Update()
{
}

