#pragma once
#include <GameEngine/GameEngine.h>

//
class Worms : public GameEngine
{
public:
	// constrcuter destructer
	Worms();
	~Worms();

	// delete Function
	Worms(const Worms& _Other) = delete;
	Worms(Worms&& _Other) noexcept = delete;
	Worms& operator=(const Worms& _Other) = delete;
	Worms& operator=(Worms&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

