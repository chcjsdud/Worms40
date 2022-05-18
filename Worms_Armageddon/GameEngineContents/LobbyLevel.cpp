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
	CreateActor<Cursor>(static_cast<int>(ActorGroup::UI));
	BackGround_ = CreateActor<LobbyBackGround>(static_cast<int>(ActorGroup::UI));
	PlayersBox_ = CreateActor<PlayersBox>(static_cast<int>(ActorGroup::UI));
}

void LobbyLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayersBox_->SetPosition(float4{ 15, 15 });
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackGround_->Death();
}


void LobbyLevel::Update()
{
	// 로비 -> 플레이 레벨로
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

}

