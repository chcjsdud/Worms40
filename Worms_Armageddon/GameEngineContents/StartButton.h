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

	inline bool IsGameStartAvailable()
	{
		return IsGameStart_;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;

	void OnClickButton();
private:
	void ActivateCheck();

private:
	GameEngineRenderer* ButtonRenderer_;

	bool IsGameStart_;
};

