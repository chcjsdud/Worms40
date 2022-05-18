#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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

	int a = 0;



};

