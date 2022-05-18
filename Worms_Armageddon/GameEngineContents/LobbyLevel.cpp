#include "LobbyLevel.h"
#include "LobbyBackGround.h"
#include "PlayersBox.h"
#include "Cursor.h"
#include "Enums.h"

#include <GameEngine/GameEngine.h>
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
	CreateActor<PlayersBox>(static_cast<int>(ActorGroup::UI));
	CreateActor<Cursor>(static_cast<int>(ActorGroup::UI));
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackGround_->Death();
}


void LobbyLevel::Update()
{

	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

}

