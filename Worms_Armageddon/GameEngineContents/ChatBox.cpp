#include "ChatBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

ChatBox::ChatBox() 
	: BoxRenderer_(nullptr)
{
}

ChatBox::~ChatBox() 
{
}

void ChatBox::Start()
{
	BoxRenderer_ = CreateRenderer(static_cast<int>(RenderOrder::BackGround_1));
	BoxRenderer_->SetImage("13268.bmp");
	BoxRenderer_->SetScale(float4{ 1248, 318});
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

	GetLevel()->RegistActor("ChatBox", this);

}

void ChatBox::Update()
{
	int size = ChatList_.size();
	for (int i = 0; i < size; ++i)
	{
		ChatList_[i]->SetPosition({30.f , 800.f - ((size - i) * 20.f)});
	}

	if (size > 15)
	{
		ChatList_[0]->Death();

		std::vector<Font*>::iterator Iter;
		Iter = ChatList_.begin();
		(*Iter)->Death();
		ChatList_.erase(Iter);
	}
}

void ChatBox::CreateChatList(std::string _Chat)
{
	Font* Font_ = GetLevel()->CreateActor<Font>();
	Font_->GameContentCreateFont(_Chat, {0,0});
	ChatList_.push_back(Font_);

}

