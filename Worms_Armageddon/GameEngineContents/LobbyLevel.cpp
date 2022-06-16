#include "LobbyHeaders.h"
#include "Cursor.h"
#include "GameOptions.h"
#include "Enums.h"
#include "TeamButton.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineBase/GameEngineRandom.h>

LobbyLevel::LobbyLevel()
	: BackGround_(nullptr)
	, PlayersBox_(nullptr)
	, TeamEditBox_(nullptr)
	, TeamListBox_(nullptr)
	, ChatBox_(nullptr)
	, TypingBox_(nullptr)
	, TerrainBox_(nullptr)
	, LobbySettings_(nullptr)
	, ReadyButton_(nullptr)
	, StartButton_(nullptr)
	, ExitButton_(nullptr)
	, LobbyShootingStar_(nullptr)
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
	TeamEditBox_ = CreateActor<TeamEditBox>(static_cast<int>(ActorGroup::UI));
	ChatBox_ = CreateActor<ChatBox>(static_cast<int>(ActorGroup::UI));
	TypingBox_ = CreateActor<TypingBox>(static_cast<int>(ActorGroup::UI));
	TerrainBox_ = CreateActor<TerrainBox>(static_cast<int>(ActorGroup::UI));

	LobbySettings_ = CreateActor<LobbySettings>(static_cast<int>(ActorGroup::UI));

	// 버튼
	ReadyButton_ = CreateActor<ReadyButton>(static_cast<int>(ActorGroup::UI));
	StartButton_ = CreateActor<StartButton>(static_cast<int>(ActorGroup::UI));
	ExitButton_ = CreateActor<ExitButton>(static_cast<int>(ActorGroup::UI));

	LobbyShootingStar_ = CreateActor<LobbyShootingStar>(static_cast<int>(ActorGroup::UI));

	//채팅 
	ChattingBox_ = CreateActor<ChattingBox>();

	//
	GameEngineInput::GetInst()->CreateKey("ChatKeyA", 'A');
	GameEngineInput::GetInst()->CreateKey("ChatKeyB", 'B');
	GameEngineInput::GetInst()->CreateKey("ChatKeyC", 'C');
	GameEngineInput::GetInst()->CreateKey("ChatKeyD", 'D');
	GameEngineInput::GetInst()->CreateKey("ChatKeyE", 'E');
	GameEngineInput::GetInst()->CreateKey("ChatKeyF", 'F');
	GameEngineInput::GetInst()->CreateKey("ChatKeyG", 'G');
	GameEngineInput::GetInst()->CreateKey("ChatKeyH", 'H');
	GameEngineInput::GetInst()->CreateKey("ChatKeyI", 'I');
	GameEngineInput::GetInst()->CreateKey("ChatKeyJ", 'J');
	GameEngineInput::GetInst()->CreateKey("ChatKeyK", 'K');
	GameEngineInput::GetInst()->CreateKey("ChatKeyL", 'L');
	GameEngineInput::GetInst()->CreateKey("ChatKeyM", 'M');
	GameEngineInput::GetInst()->CreateKey("ChatKeyN", 'N');
	GameEngineInput::GetInst()->CreateKey("ChatKeyO", 'O');
	GameEngineInput::GetInst()->CreateKey("ChatKeyP", 'P');
	GameEngineInput::GetInst()->CreateKey("ChatKeyQ", 'Q');
	GameEngineInput::GetInst()->CreateKey("ChatKeyR", 'R');
	GameEngineInput::GetInst()->CreateKey("ChatKeyS", 'S');
	GameEngineInput::GetInst()->CreateKey("ChatKeyT", 'T');
	GameEngineInput::GetInst()->CreateKey("ChatKeyU", 'U');
	GameEngineInput::GetInst()->CreateKey("ChatKeyV", 'V');
	GameEngineInput::GetInst()->CreateKey("ChatKeyW", 'W');
	GameEngineInput::GetInst()->CreateKey("ChatKeyX", 'X');
	GameEngineInput::GetInst()->CreateKey("ChatKeyY", 'Y');
	GameEngineInput::GetInst()->CreateKey("ChatKeyZ", 'Z');

	GameEngineInput::GetInst()->CreateKey("ChatKeySmalla", 'a');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallb", 'b');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallc", 'c');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalld", 'd');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalle", 'e');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallf", 'f');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallg", 'g');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallh", 'h');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalli", 'i');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallj", 'j');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallk", 'k');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalll", 'l');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallm", 'm');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalln", 'n');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallo", 'o');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallp", 'p');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallq", 'q');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallr", 'r');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmalls", 's');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallt", 't');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallu", 'u');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallv", 'v');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallw", 'w');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallx", 'x');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmally", 'y');
	GameEngineInput::GetInst()->CreateKey("ChatKeySmallz", 'z');

	GameEngineInput::GetInst()->CreateKey("ChatKey0", '0');
	GameEngineInput::GetInst()->CreateKey("ChatKey1", '1');
	GameEngineInput::GetInst()->CreateKey("ChatKey2", '2');
	GameEngineInput::GetInst()->CreateKey("ChatKey3", '3');
	GameEngineInput::GetInst()->CreateKey("ChatKey4", '4');
	GameEngineInput::GetInst()->CreateKey("ChatKey5", '5');
	GameEngineInput::GetInst()->CreateKey("ChatKey6", '6');
	GameEngineInput::GetInst()->CreateKey("ChatKey7", '7');
	GameEngineInput::GetInst()->CreateKey("ChatKey8", '8');
	GameEngineInput::GetInst()->CreateKey("ChatKey9", '9');

	GameEngineInput::GetInst()->CreateKey("ChatKeyGrave_Exclamaion_Mark", '!');
	GameEngineInput::GetInst()->CreateKey("ChatKeyGrave_Empty", ' ');

	GameEngineInput::GetInst()->CreateKey("EnterChat", VK_RETURN);
	GameEngineInput::GetInst()->CreateKey("BackSpace", VK_BACK);

}

void LobbyLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayersBox_->SetPosition({ 16, 13 });
	TeamEditBox_->SetPosition({ 260, 16 });
	ChatBox_->SetPosition({ 16, 477 });
	TypingBox_->SetPosition({ 16, 814 });
	TerrainBox_->SetPosition({ 785, 22 });

	LobbySettings_->SetPosition({ 580, 260 });

	// 버튼
	ReadyButton_->SetPosition({ 19, 299 });
	StartButton_->SetPosition({ 966, 814 });
	ExitButton_->SetPosition({ 966, 892 });

	LobbyShootingStar_->SetPosition({0,0});

	SoundPlayer_ = GameEngineSound::SoundPlayControl("menu-loop.wav", 1000);
	SoundPlayer_.Volume(SND_VOL_LOBBYBGM);

}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// 플레이 레벨로 넘겨주는 정보
	TeamEditBox* TeamEditBoxPtr = dynamic_cast<TeamEditBox*>(TeamEditBox_);
	LobbySettings* LobbySettingsPtr = dynamic_cast<LobbySettings*>(LobbySettings_);
	// PlayerNum
	int PlayerNum = TeamEditBoxPtr->GetSelectedTeamNum();

	// TeamColor & TeamNum
	std::list<TeamButton*> TeamButtons = TeamEditBoxPtr->GetSelectedTeams();
	for (auto Button : TeamButtons)
	{
		TeamColor Color = Button->GetTeamColor();
		int Num = Button->GetTeamNum();
		GameOptions::PlayingOptions.SetPlayerTeamSetting(Color, Num);
	}

	// Turn Time
	int TurnTime = LobbySettingsPtr->GetTurnTime();
	GameOptions::PlayingOptions.SetTurnTime(TurnTime);
	
	// 디버깅용 레벨 넘길 때
	if (0 == PlayerNum && static_cast<int>(TeamButtons.size()) == 0 
		&& TurnTime == 45 && MapType::Other == GameOptions::PlayingOptions.GetMapType())
	{
		GameOptions::PlayingOptions.SetTurnTime(45);
		GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)0, 1);
		//GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)2, 3);
		//GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)4, 3);
	}

	SoundPlayer_.Stop();
}


void LobbyLevel::Update()
{
	// 로비 -> 플레이 레벨로
	// 디버깅용
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	// 시작 버튼 누름
	StartButton* StartButtonPtr = dynamic_cast<StartButton*>(StartButton_);
	if (true == StartButtonPtr->IsGameStartAvailable())
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	// 준비 버튼 누루면 전구를 모두 껏다 킴
	PlayerReadyCheck();
}

void LobbyLevel::PlayerReadyCheck()
{
	TeamEditBox* TeamEditBoxPtr = dynamic_cast<TeamEditBox*>(TeamEditBox_);
	ReadyButton* ReadyButtonPtr = dynamic_cast<ReadyButton*>(ReadyButton_);
	StartButton* StartButtonPtr = dynamic_cast<StartButton*>(StartButton_);
	PlayersBox* PlayersBoxPtr = dynamic_cast<PlayersBox*>(PlayersBox_);

	// 선택팀 1개 이상이어야 Ready 가능
	auto val = GameOptions::PlayingOptions.GetMapType();
	if (1 > TeamEditBoxPtr->GetSelectedTeamNum() || MapType::Other == GameOptions::PlayingOptions.GetMapType())
	{
		ReadyButtonPtr->SetReadyImpossible();
		ReadyButtonPtr->SetPlayerReady(false);
		StartButtonPtr->SetActivate(false);
		PlayersBoxPtr->BulbOff();
		return;
	}
	ReadyButtonPtr->SetReadyPossible();
	bool PlayerReady = ReadyButtonPtr->GetPlayerReady();

	// 게임시작 버튼, 전구 On/Off
	if (true == PlayerReady)
	{
		StartButtonPtr->SetActivate(true);
		PlayersBoxPtr->BulbOn();
	}
	else
	{
		StartButtonPtr->SetActivate(false);
		PlayersBoxPtr->BulbOff();
	}



}

