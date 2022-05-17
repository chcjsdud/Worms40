#include "LobbyLevel.h"
#include "LobbyBackGround.h"
#include "Enums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineInput.h>


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
	BackGround_ = CreateActor<LobbyBackGround>(static_cast<int>(ActorGroup::UI));
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackGround_->Death();
}


void LobbyLevel::Update()
{
	
}

