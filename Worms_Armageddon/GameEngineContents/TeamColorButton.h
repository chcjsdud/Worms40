#pragma once
#include "Button.h"
#include "Enums.h"
#include <string>

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

	inline void SetColor(TeamColor _Color)
	{
		TeamColor_ = _Color;
	}

	inline TeamColor GetColor()
	{
		return TeamColor_;
	}

protected:
	void Start() override;
	void Update() override;
	void OnClickButton() override;

private:
	void TeamColorNameUpdate();

private:
	TeamColor TeamColor_;
};

