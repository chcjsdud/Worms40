#include "LobbyLevel.h"
#include "LobbyBackGround.h"
#include "PlayersBox.h"
#include "TeamListBox.h"
#include "TeamEditBox.h"
#include "Cursor.h"
#include "Enums.h"

#include "GameOptions.h"

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
	TeamListBox_ = CreateActor<TeamListBox>(static_cast<int>(ActorGroup::UI));
	TeamEditBox_ = CreateActor<TeamEditBox>(static_cast<int>(ActorGroup::UI));

}

void LobbyLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayersBox_->SetPosition(float4{ 16, 13 });
	TeamListBox_->SetPosition(float4{ 260, 13 });
}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// 테스트 플레이레벨로 넘겨주는 정보
	GameOptions::PlayingOptions.SetPlayerName(0, "FirstPlayer");
	GameOptions::PlayingOptions.SetPlayerColor(0, RGB(255,255,255));
	GameOptions::PlayingOptions.SetTurnTime(45);
	GameOptions::PlayingOptions.SetPlayerNum(3);
	GameOptions::PlayingOptions.SetMapType(MapType::MAPBOOKS);

}


void LobbyLevel::Update()
{
	// 로비 -> 플레이 레벨로
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

}

