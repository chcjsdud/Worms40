
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

	// 버튼
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

	//TODO:: 지금은 통 이미지, 리소스 구하기
	LobbySettings_->SetPosition({ 580, 260 });

	// 버튼
	ReadyButton_->SetPosition({ 19, 299 });
	StartButton_->SetPosition({ 966, 814 });
	ExitButton_->SetPosition({ 966, 892 });

	//폰트
	FontTest_ = CreateActor<Font>(static_cast<int>(RenderOrder::Font));
	FontTest_->SetPosition({ 0,100 });
	std::string TestText = "dslilili      iiiiifsf";
	FontTest_->GameContentCreateFont(TestText, float4({ 100,100 }));

}

void LobbyLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// 테스트 플레이레벨로 넘겨주는 정보
	//GameOptions::PlayingOptions.SetPlayerName(0, "FirstPlayer");
	//GameOptions::PlayingOptions.SetPlayerColor(0, RGB(255, 255, 255));
	GameOptions::PlayingOptions.SetTurnTime(45);
	// GameOptions::PlayingOptions.SetPlayerNum(3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)0, 3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)1, 3);
	GameOptions::PlayingOptions.SetPlayerTeamSetting((TeamColor)2, 3);
	GameOptions::PlayingOptions.SetMapType(MapType::Books);

	// TODO::체력 100, 200 중 세팅값 보내기
	GameOptions::PlayingOptions.SetWormzHp(200);
}


void LobbyLevel::Update()
{
	// 로비 -> 플레이 레벨로
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	// 준비 버튼 누루면 전구를 모두 껏다 킴
	PlayerBulbOnOff();

	// TODO::팀이 1개라도 있어야 준비버튼 클릭 가능


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

