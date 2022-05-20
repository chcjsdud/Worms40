#include "MainLogo.h"
#include "TitleLevel.h"
#include <GameEngine/GameEngineRenderer.h>

MainLogo::MainLogo()
	:
	MainLogoRenderer_(nullptr),
	CircleRenderer_(nullptr),

	AnimationTimer_(0.f),

	MainLogoState_(MAINLOGO_STATE::FadeOut),
	AnimationState_(ANIMATION_STATE::Init)
{
}

MainLogo::~MainLogo()
{
}

void MainLogo::Start()
{
	MainLogoRenderer_ = CreateRenderer("Title_Logo.bmp");
	MainLogoRenderer_->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::MainLogo));

	CircleRenderer_ = CreateRenderer("TitleLogo_Actor.bmp");
	CircleRenderer_->SetPivot({-105.f, 0});
	CircleRenderer_->CreateAnimation("TitleLogo_Actor.bmp", "TITLE_LOGO_ANIMATION", 0, 4, 0.150f, true);
	CircleRenderer_->CreateAnimation("TitleLogo_Actor.bmp", "TITLE_LOGO_INIT", 0, 0, 0, false);
	CircleRenderer_->ChangeAnimation("TITLE_LOGO_INIT");
	CircleRenderer_->SetOrder(static_cast<int>(TITLE_RENDER_ORDER::MainLogo));

}

void MainLogo::Update()
{
	switch (MainLogoState_)
	{
	case MAINLOGO_STATE::FadeOut:

		break;
	case MAINLOGO_STATE::Update:
		LogoAnimation();

		break;
	case MAINLOGO_STATE::StopUpdate:

		break;
	default:
		break;

	}

}

void MainLogo::LogoAnimation()
{
	switch (AnimationState_)
	{
	case ANIMATION_STATE::Init:
		AnimationTimer_ += GameEngineTime::GetInst()->GetDeltaTime();
		if (AnimationTimer_ > 0.5f)
		{
			AnimationTimer_ = 0.f;
			CircleRenderer_->ChangeAnimation("TITLE_LOGO_ANIMATION");
			AnimationState_ = ANIMATION_STATE::Animation;
		}
		break;
	case ANIMATION_STATE::Animation:

		if (CircleRenderer_->IsEndAnimation())
		{
			CircleRenderer_->ChangeAnimation("TITLE_LOGO_INIT");
			AnimationState_ = ANIMATION_STATE::Init;
		}

		break;

	default:
		break;
	}
}

void MainLogo::LogoStateSetUpdate()
{
	MainLogoState_ = MAINLOGO_STATE::Update;
}

void MainLogo::LogoStateSetStopAndChangeAnimation()
{
	MainLogoState_ = MAINLOGO_STATE::StopUpdate;
	CircleRenderer_->ChangeAnimation("TITLE_LOGO_INIT");
}
