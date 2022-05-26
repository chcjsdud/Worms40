#pragma once
#include "Button.h"

// Ό³Έν :
class TeamColorButton : public Button
{
public:
	// constrcuter destructer
	TeamColorButton();
	~TeamColorButton();

	// delete Function
	TeamColorButton(const TeamColorButton& _Other) = delete;
	TeamColorButton(TeamColorButton&& _Other) noexcept = delete;
	TeamColorButton& operator=(const TeamColorButton& _Other) = delete;
	TeamColorButton& operator=(TeamColorButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void OnClickButton() override;

private:

};

