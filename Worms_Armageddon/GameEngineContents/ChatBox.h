#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class ChatBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ChatBox();
	~ChatBox();

	// delete Function
	ChatBox(const ChatBox& _Other) = delete;
	ChatBox(ChatBox&& _Other) noexcept = delete;
	ChatBox& operator=(const ChatBox& _Other) = delete;
	ChatBox& operator=(ChatBox&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* BoxRenderer_;
};

