#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class TypingBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TypingBox();
	~TypingBox();

	// delete Function
	TypingBox(const TypingBox& _Other) = delete;
	TypingBox(TypingBox&& _Other) noexcept = delete;
	TypingBox& operator=(const TypingBox& _Other) = delete;
	TypingBox& operator=(TypingBox&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* BoxRenderer_;

};

