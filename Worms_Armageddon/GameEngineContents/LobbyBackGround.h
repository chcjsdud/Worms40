#pragma once

// Ό³Έν :
class LobbyBackGround
{
public:
	// constrcuter destructer
	LobbyBackGround();
	~LobbyBackGround();

	// delete Function
	LobbyBackGround(const LobbyBackGround& _Other) = delete;
	LobbyBackGround(LobbyBackGround&& _Other) noexcept = delete;
	LobbyBackGround& operator=(const LobbyBackGround& _Other) = delete;
	LobbyBackGround& operator=(LobbyBackGround&& _Other) noexcept = delete;

protected:

private:

};

