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

	inline void SwitchPlayerReady()
	{
		IsPlayerReady_ = !IsPlayerReady_;
	}

	inline bool GetPlayerReady()
	{
		return IsPlayerReady_;
	}

	inline void SetPlayerReady(bool _Value)
	{
		IsPlayerReady_ = _Value;
	}

	inline void SetReadyPossible()
	{
		IsReadyPossible_ = true;
	}

	inline void SetReadyImpossible()
	{
		IsReadyPossible_ = false;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;

	virtual void OnClickButton() override;

private:
	void ButtonNameUpdate();

private:
	bool IsReadyPossible_;
	bool IsPlayerReady_;
};

