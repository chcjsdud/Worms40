#pragma once
#include "Button.h"

// Ό³Έν :
class TeamNumButton : public Button
{
public:
	// constrcuter destructer
	TeamNumButton();
	~TeamNumButton();

	// delete Function
	TeamNumButton(const TeamNumButton& _Other) = delete;
	TeamNumButton(TeamNumButton&& _Other) noexcept = delete;
	TeamNumButton& operator=(const TeamNumButton& _Other) = delete;
	TeamNumButton& operator=(TeamNumButton&& _Other) noexcept = delete;

	inline void SetTeamNumber(int _Number)
	{
		TeamNum_ = _Number;
	}

	inline int GetNum()
	{
		return TeamNum_;
	}

protected:
	void Start() override;
	void Update() override;
	void OnClickButton() override;

private:
	void SetTeamNumButtonName();

private:

	int TeamNum_;
};

