#include "TitleLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <sstream>


TitleLevel::TitleLevel()
	:
	StartLogo_(nullptr),
	MainLogo_(nullptr),
	TitleBackGround_(nullptr),
	WhiteFadeOut_(nullptr),
	BlackFadeInOut_(nullptr),

	FontCount_(1),

	FontTimer_(0.f),
	BlackFadeInOutAlpha_(0.f),
	WhiteFadeOutAlpha_(255.f),

	TitleState_(TITLE_STATE::StartLogo)
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	TitleBackGround_ = CreateActor<TitleImage>();
	TitleBackGround_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  GameEngineWindow::GetInst().GetScale().Half().y });
	TitleBackGround_->GetRenderer()->SetImage("backGround.bmp");
	TitleBackGround_->GetRenderer()->SetScale({ 1280.f, 960.f });
	TitleBackGround_->GetRenderer()->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::BackGround));

	StartLogo_ = CreateActor<StartLogo>();
	StartLogo_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  GameEngineWindow::GetInst().GetScale().Half().y });
	StartLogo_->GetRenderer()->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::StartLogo));

	BlackFadeInOut_ = CreateActor<TitleImage>();
	BlackFadeInOut_->GetRenderer()->SetImage("Fade_Black.bmp");
	BlackFadeInOut_->GetRenderer()->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::FadeInOut));
	BlackFadeInOut_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  GameEngineWindow::GetInst().GetScale().Half().y });
	BlackFadeInOut_->Off();
}

void TitleLevel::Update()
{
	switch (TitleState_)
	{
	case TITLE_STATE::StartLogo:

		//시작 로고가 나오고 2초 뒤에 페이드 아웃 시작. 그리고 메인 로고 등장.
		if (StartLogo_->GetAccTime() > 2.f)
		{
			BlackFadeInOut_->On();
			BlackFadeInOutAlpha_ += 5.f + (GameEngineTime::GetInst()->GetDeltaTime());
			BlackFadeInOut_->GetRenderer()->SetAlpha(static_cast<unsigned int>(BlackFadeInOutAlpha_));

			if (BlackFadeInOutAlpha_ >= 255.f)
			{
				BlackFadeInOutAlpha_ = 255.f;

				StartLogo_->Death();
				StartLogo_ = nullptr;

				MainLogo_ = CreateActor<MainLogo>();
				MainLogo_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  150.f });
				MainLogo_->LogoStateSetUpdate();

				TitleState_ = TITLE_STATE::MainLogo;
				break;
			}
		}

		break;
	case TITLE_STATE::MainLogo:

		// 메인 로고가 나오고 5초 이후에 화이트 페이드 아웃
		BlackFadeInOutAlpha_ -= 5.f + (GameEngineTime::GetInst()->GetDeltaTime());
		BlackFadeInOut_->GetRenderer()->SetAlpha(static_cast<unsigned int>(BlackFadeInOutAlpha_));

		if (BlackFadeInOutAlpha_ <= 0)
		{
			BlackFadeInOut_->Off();
			BlackFadeInOutAlpha_ = 0.f;
		}

		if (MainLogo_->GetAccTime() > 5.f)
		{
			MainLogo_->LogoStateSetStopAndChangeAnimation();

			TitleBackGround_->GetRenderer()->SetImage("Title_Back_Edit.bmp");
			TitleBackGround_->GetRenderer()->SetScale(GameEngineWindow::GetInst().GetScale());

			WhiteFadeOut_ = CreateActor<TitleImage>();
			WhiteFadeOut_->GetRenderer()->SetImage("Fade_White.bmp");
			WhiteFadeOut_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  GameEngineWindow::GetInst().GetScale().Half().y });

			WhiteFadeOut_->GetRenderer()->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::FadeInOut));

			TitleState_ = TITLE_STATE::WhiteFadeOut;
		}

		break;
	case TITLE_STATE::WhiteFadeOut:

		WhiteFadeOutAlpha_ -= 5.f + (GameEngineTime::GetInst()->GetDeltaTime());
		WhiteFadeOut_->GetRenderer()->SetAlpha(static_cast<unsigned int>(WhiteFadeOutAlpha_));

		if (WhiteFadeOutAlpha_ <= 0.f)
		{
			TitleState_ = TITLE_STATE::FontUpdate;
		}

		break;
	case TITLE_STATE::FontUpdate:

		FontTimer_ += GameEngineTime::GetInst()->GetDeltaTime();

		if (FontTimer_ > 0.2f)
		{
			FontTimer_ = 0.f;
			std::stringstream ssInt;
			ssInt << FontCount_;
			std::string FileName = "Title_Font_" + ssInt.str() + ".bmp";
			TitleBackGround_->GetRenderer()->SetImage(FileName);
			++FontCount_;
			if (FontCount_ >= 11)
			{
				TitleState_ = TITLE_STATE::Update;
				break;
			}
		}

		break;
	case TITLE_STATE::Update:

		break;
	}

	//레벨 이동

	if (true == GameEngineInput::GetInst()->IsPress(KEY_CHANGE_PLAYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_PLAY_LEVEL);
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_CHANGE_LOBBYLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_LOBBY_LEVEL);
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_CHANGE_CREDITLEVEL))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_CREDIT_LEVEL);
	}

}
