#pragma once
#include <GameEngine/GameEngineActor.h>
#include <string>
#include "Button.h"

// Ό³Έν :
class GameEngineRenderer;
class ReadyButton : public Button
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

	inline void OnMouseEnter()
	{
		IsMouseIn_ = true;
	}

	inline void OnMouseExit()
	{
		IsMouseIn_ = false;
	}

	inline void SwitchPlayerReady()
	{
		IsPlayerReady_ = !IsPlayerReady_;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	void OnClickButton();
	void ButtonNameUpdate();

private:
	MOUSE_STATE MouseState_;

	bool IsMouseIn_;
	bool IsPlayerReady_;
};

