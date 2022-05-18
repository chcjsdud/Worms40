#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "StartLogo.h"
#include "MainLogo.h"
#include "TitleImage.h"

enum class TITLE_STATE
{
	StartLogo,
	MainLogo,
	WhiteFadeOut,
	Update,
};

enum class TITLE_RENDER_ORDER
{
	BackGround,
	StartLogo,
	MainLogo,
	FadeInOut
};



// Ό³Έν :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:
	StartLogo* StartLogo_;
	MainLogo* MainLogo_;

	TitleImage* TitleBackGround_;
	TitleImage* WhiteFadeOut_;
	TitleImage* BlackFadeInOut_;

	float WhiteFadeOutAlpha_;
	float BlackFadeInOutAlpha_;

	TITLE_STATE TitleState_;


};

