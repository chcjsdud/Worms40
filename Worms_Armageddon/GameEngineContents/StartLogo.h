#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class StartLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	StartLogo();
	~StartLogo();

	// delete Function
	StartLogo(const StartLogo& _Other) = delete;
	StartLogo(StartLogo&& _Other) noexcept = delete;
	StartLogo& operator=(const StartLogo& _Other) = delete;
	StartLogo& operator=(StartLogo&& _Other) noexcept = delete;

protected:

	virtual void Start() override;
	virtual void Update() override;

private:

	GameEngineRenderer* StartLogoRenderer_;



public:

	GameEngineRenderer* GetRenderer()
	{
		return StartLogoRenderer_;
	}

};

