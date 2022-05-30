#pragma once
#include "Button.h"

// ���� :
class TeamHandicapButton : public Button
{
public:
	// constrcuter destructer
	TeamHandicapButton();
	~TeamHandicapButton();

	// delete Function
	TeamHandicapButton(const TeamHandicapButton& _Other) = delete;
	TeamHandicapButton(TeamHandicapButton&& _Other) noexcept = delete;
	TeamHandicapButton& operator=(const TeamHandicapButton& _Other) = delete;
	TeamHandicapButton& operator=(TeamHandicapButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void OnClickButton() override;

private:

};

