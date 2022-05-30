#pragma once
#include "Button.h"
#include <string>

// 설명 : 1-UP, 팀 색, 팀원 수 정하는 버튼들의 그룹
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

	int GetButtonIndex()
	{
		return ButtonIndex_;
	}

	void SetAllButtonPosition(const float4 _Value);

protected:
	void Start() override;
	void Update() override;
	
	void OnClickButton() override;

private:
	void TeamSettingActivate();

private:
	bool IsSelected_;
	bool IsSwaping_;
	int ButtonIndex_;

	class TeamHandicapButton* HandicapButton_;
	class TeamColorButton* ColorButton_;
	class TeamNumButton* NumButton_;
};

