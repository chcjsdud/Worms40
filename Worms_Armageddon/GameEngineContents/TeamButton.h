#pragma once
#include "Button.h"
#include <string>
// Ό³Έν :
class TeamButton : public Button
{
public:
	// constrcuter destructer
	TeamButton();
	~TeamButton();

	// delete Function
	TeamButton(const TeamButton& _Other) = delete;
	TeamButton(TeamButton&& _Other) noexcept = delete;
	TeamButton& operator=(const TeamButton& _Other) = delete;
	TeamButton& operator=(TeamButton&& _Other) noexcept = delete;

	void SetButton(int _BtnNum);
	inline bool GetSelected()
	{
		return IsSelected_;
	}

protected:
	void Start() override;
	void Update() override;
	
	void OnClickButton() override;

private:
	bool IsSelected_;
};

