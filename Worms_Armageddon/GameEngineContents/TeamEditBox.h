#pragma once

// Ό³Έν :
class TeamEditBox
{
public:
	// constrcuter destructer
	TeamEditBox();
	~TeamEditBox();

	// delete Function
	TeamEditBox(const TeamEditBox& _Other) = delete;
	TeamEditBox(TeamEditBox&& _Other) noexcept = delete;
	TeamEditBox& operator=(const TeamEditBox& _Other) = delete;
	TeamEditBox& operator=(TeamEditBox&& _Other) noexcept = delete;

protected:

private:

};

