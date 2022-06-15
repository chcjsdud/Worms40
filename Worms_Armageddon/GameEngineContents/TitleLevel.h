#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "StartLogo.h"
#include "MainLogo.h"
#include "TitleImage.h"

enum class TITLE_STATE
{
	StartLogo,
	MainLogo,
	WhiteFadeOut,
	FontUpdate,
	Update,
};

enum class TITLE_RENDER_ORDER
{
	BackGround,
	StartLogo,
	MainLogo,
	FadeInOut
};



// 설명 :
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

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	StartLogo* StartLogo_;
	MainLogo* MainLogo_;

	TitleImage* TitleBackGround_;
	TitleImage* WhiteFadeOut_;
	TitleImage* BlackFadeInOut_;

	int FontCount_;

	float WhiteFadeOutAlpha_;
	float BlackFadeInOutAlpha_;

	float FontTimer_;

	TITLE_STATE TitleState_;

	// 사운드
	GameEngineSoundPlayer Sound_Heart;
	GameEngineSoundPlayer Sound_Bomb;
	GameEngineSoundPlayer Sound_Title;

	bool SoundOn_Heart;
	bool SoundOn_Bomb;
	bool SoundOn_Title;
};

