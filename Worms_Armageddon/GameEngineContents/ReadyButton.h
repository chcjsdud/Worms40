#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class ReadyButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ReadyButton();
	~ReadyButton();

	// delete Function
	ReadyButton(const ReadyButton& _Other) = delete;
	ReadyButton(ReadyButton&& _Other) noexcept = delete;
	ReadyButton& operator=(const ReadyButton& _Other) = delete;
	ReadyButton& operator=(ReadyButton&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* BoxRenderer_;
};

