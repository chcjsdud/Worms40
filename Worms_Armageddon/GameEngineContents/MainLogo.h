#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :

enum class MAINLOGO_STATE
{
	FadeOut,
	Update,
	StopUpdate,
};

enum class ANIMATION_STATE
{
	Init,
	Animation,
	End
};


class GameEngineRenderer;
class MainLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	MainLogo();
	~MainLogo();

	// delete Function
	MainLogo(const MainLogo& _Other) = delete;
	MainLogo(MainLogo&& _Other) noexcept = delete;
	MainLogo& operator=(const MainLogo& _Other) = delete;
	MainLogo& operator=(MainLogo&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* MainLogoRenderer_;
	GameEngineRenderer* CircleRenderer_;

	MAINLOGO_STATE MainLogoState_;
	ANIMATION_STATE AnimationState_;

	float AnimationTimer_;

private:
	void LogoAnimation();

public:
	void LogoStateSetUpdate();
	void LogoStateSetStopAndChangeAnimation();		//로고 스테이트 변경 및 애니메이션 체인지


};

