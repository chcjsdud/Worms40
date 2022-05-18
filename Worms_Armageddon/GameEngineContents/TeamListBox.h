#pragma once

// Ό³Έν :
class TeamListBox
{
public:
	// constrcuter destructer
	TeamListBox();
	~TeamListBox();

	// delete Function
	TeamListBox(const TeamListBox& _Other) = delete;
	TeamListBox(TeamListBox&& _Other) noexcept = delete;
	TeamListBox& operator=(const TeamListBox& _Other) = delete;
	TeamListBox& operator=(TeamListBox&& _Other) noexcept = delete;

protected:

private:

};

