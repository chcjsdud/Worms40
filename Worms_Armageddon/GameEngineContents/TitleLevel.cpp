#include "TitleLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


TitleLevel::TitleLevel()
	:
	StartLogo_(nullptr),
	MainLogo_(nullptr),
	TitleBackGround_(nullptr),
	WhiteFadeOut_(nullptr),
	BlackFadeInOut_(nullptr),

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
	TitleBackGround_->GetRenderer()->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::BackGround));

	StartLogo_ = CreateActor<StartLogo>(); 
	StartLogo_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  GameEngineWindow::GetInst().GetScale().Half().y});
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
				MainLogo_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x,  200.f });
				MainLogo_->LogoStateSetUpdate();

				TitleState_ = TITLE_STATE::MainLogo;
				break;
			}
		}

		break;
	case TITLE_STATE::MainLogo:

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

			TitleBackGround_->GetRenderer()->SetImage("Title_Backdrop.bmp");
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
			TitleState_ = TITLE_STATE::Update;
		}

		break;
	case TITLE_STATE::Update:

		break;
	default:
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

}
