#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Button.h"
// Ό³Έν :
class GameEngineRenderer;
class StartButton : public Button
{
public:
	// constrcuter destructer
	StartButton();
	~StartButton();

	// delete Function
	StartButton(const StartButton& _Other) = delete;
	StartButton(StartButton&& _Other) noexcept = delete;
	StartButton& operator=(const StartButton& _Other) = delete;
	StartButton& operator=(StartButton&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

	virtual void OnClickButton() override;
private:

};

