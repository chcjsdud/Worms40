#pragma once
#include "Button.h"
#include <string>

// Ό³Έν :
class TurnTimeButton : public Button
{
public:
	// constrcuter destructer
	TurnTimeButton();
	~TurnTimeButton();

	// delete Function
	TurnTimeButton(const TurnTimeButton& _Other) = delete;
	TurnTimeButton(TurnTimeButton&& _Other) noexcept = delete;
	TurnTimeButton& operator=(const TurnTimeButton& _Other) = delete;
	TurnTimeButton& operator=(TurnTimeButton&& _Other) noexcept = delete;

public:
	inline int GetCurrentTurnTime()
	{
		return CurrentTurnTime_;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;

	virtual void OnClickButton() override;

private:
	std::string TurnTimeToString();
	void ButtonNameUpdate();

private:
	GameEngineRenderer* ButtonRenderer_;

	std::vector<int> TurnTimes_;
	int TurnTimesIdx_;
	int CurrentTurnTime_;
};

