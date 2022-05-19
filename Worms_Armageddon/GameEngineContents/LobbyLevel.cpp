
#include "Cursor.h"
#include "GameOptions.h"
#include "Enums.h"
#include "LobbyHeaders.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineInput.h>

LobbyLevel::LobbyLevel()
	: BackGround_(nullptr)
	, PlayersBox_(nullptr)
	, TeamEditBox_(nullptr)
	, TeamListBox_(nullptr)
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
	ChatBox_ = CreateActor<ChatBox>(static_cast<int>(ActorGroup::UI));
	TypingBox_ = CreateActor<TypingBox>(static_cast<int>(ActorGroup::UI));
	RollingStar_ = CreateActor<RollingStar>(static_cast<int>(ActorGroup::UI));
	TerrainBox_ = CreateActor<TerrainBox>(static_cast<int>(ActorGroup::UI));

	LobbySettings_ = CreateActor<LobbySettings>(static_cast<int>(ActorGroup::UI));

	// ��ư
	ReadyButton_ = CreateActor<ReadyButton>(static_cast<int>(ActorGroup::UI));
	StartButton_ = CreateActor<StartButton>(static_cast<int>(ActorGroup::UI));
	ExitButton_ = CreateActor<ExitButton>(static_cast<int>(ActorGroup::UI));
}

void LobbyLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayersBox_->SetPosition({ 16, 13 });
	TeamListBox_->SetPosition({ 260, 13 });
	TeamEditBox_->SetPosition({ 260, 296 });
	ChatBox_->SetPosition({ 16, 477 });
	TypingBox_->SetPosition({ 16, 814 });
	RollingStar_->SetPosition({ 679, 100 });
	TerrainBox_->SetPosition({ 785, 22 });

	LobbySettings_->SetPosition({ 580, 260 });

	// ��ư
	ReadyButton_->SetPosition({ 19, 299 });
	StartButton_->SetPosition({ 966, 814 });
	ExitButton_->SetPosition({ 966, 892 });

}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// �׽�Ʈ �÷��̷����� �Ѱ��ִ� ����
	GameOptions::PlayingOptions.SetPlayerName(0, "FirstPlayer");
	GameOptions::PlayingOptions.SetPlayerColor(0, RGB(255,255,255));
	GameOptions::PlayingOptions.SetTurnTime(45);
	GameOptions::PlayingOptions.SetPlayerNum(3);
	GameOptions::PlayingOptions.SetMapType(MapType::MAPBOOKS);

}


void LobbyLevel::Update()
{
	// �κ� -> �÷��� ������
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

}

