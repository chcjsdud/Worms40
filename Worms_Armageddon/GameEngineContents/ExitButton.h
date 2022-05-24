#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Button.h"

// Ό³Έν :
class GameEngineRenderer;
class ExitButton : public Button
{
public:
	// constrcuter destructer
	ExitButton();
	~ExitButton();

	// delete Function
	ExitButton(const ExitButton& _Other) = delete;
	ExitButton(ExitButton&& _Other) noexcept = delete;
	ExitButton& operator=(const ExitButton& _Other) = delete;
	ExitButton& operator=(ExitButton&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

	void OnClickButton();

private:
};

