
#include "Cursor.h"
#include "GameOptions.h"
#include "Enums.h"
#include "LobbyHeaders.h"

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
	, RollingStar_(nullptr)
	, TerrainBox_(nullptr)
	, LobbySettings_(nullptr)
	, ReadyButton_(nullptr)
	, StartButton_(nullptr)
	, ExitButton_(nullptr)
	, FontTest_(nullptr)
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
	TeamEditBox_->SetPosition({ 260, 16 });
	ChatBox_->SetPosition({ 16, 477 });
	TypingBox_->SetPosition({ 16, 814 });
	RollingStar_->SetPosition({ 679, 100 });
	TerrainBox_->SetPosition({ 785, 22 });

	//TODO:: ������ �� �̹���, ���ҽ� ���ϱ�
	LobbySettings_->SetPosition({ 580, 260 });

	// ��ư
	ReadyButton_->SetPosition({ 19, 299 });
	StartButton_->SetPosition({ 966, 814 });
	ExitButton_->SetPosition({ 966, 892 });

	//��Ʈ
	FontTest_ = CreateActor<Font>(static_cast<int>(RenderOrder::Font));
	FontTest_->SetPosition({ 0,100 });
	std::string TestText = "dslilili      iiiiifsf";
	FontTest_->GameContentCreateFont(TestText, float4({ 100,100 }));

}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// �׽�Ʈ �÷��̷����� �Ѱ��ִ� ����
	//GameOptions::PlayingOptions.SetPlayerName(0, "FirstPlayer");
	//GameOptions::PlayingOptions.SetPlayerColor(0, RGB(255, 255, 255));
	GameOptions::PlayingOptions.SetTurnTime(45);
	// GameOptions::PlayingOptions.SetPlayerNum(3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)0, 3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)1, 3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)2, 3);
	GameOptions::PlayingOptions.SetMapType(MapType::Books);

	// TODO::ü�� 100, 200 �� ���ð� ������
	GameOptions::PlayingOptions.SetWormzHp(200);
}


void LobbyLevel::Update()
{
	// �κ� -> �÷��� ������
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	// �غ� ��ư ����� ������ ��� ���� Ŵ
	PlayerBulbOnOff();

	// TODO::���� 1���� �־�� �غ��ư Ŭ�� ����


}

void LobbyLevel::PlayerBulbOnOff()
{
	ReadyButton* readyButton = dynamic_cast<ReadyButton*>(ReadyButton_);
	bool PlayerReady = readyButton->GetPlayerReady();

	PlayersBox* playersBox = dynamic_cast<PlayersBox*>(PlayersBox_);

	if (true == PlayerReady)
	{
		playersBox->BulbOn();
	}
	else
	{
		playersBox->BulbOff();
	}
}

