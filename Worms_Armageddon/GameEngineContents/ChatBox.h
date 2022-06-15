#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"
#include <vector>

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
	std::vector<Font*> ChatList_;

public:
	void CreateChatList(std::string _Chat);
};

