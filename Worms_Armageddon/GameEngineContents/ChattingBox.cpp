#include "ChattingBox.h"
#include "ChatBox.h"
#include <GameEngineBase/GameEngineInput.h>

ChattingBox::ChattingBox() 
	:
	  ChattingBox_(nullptr)
	, Font_(nullptr)
	, String_()
{


}

ChattingBox::~ChattingBox() 
{
}

void ChattingBox::Start()
{
	Font_ = GetLevel()->CreateActor<Font>();
	Font_->GameContentCreateFont(" ", {0, 0});

	this->SetPosition({30.f, 830.f});
	Font_->SetPosition({ 30.f, 830.f });
}

void ChattingBox::Update()
{

	for (char c = 'a'; c <= 122; ++c)
	{
		std::string ssChar;
		ssChar += c;

		if (GameEngineInput::GetInst()->IsDown("ChatKeySmall" + ssChar))
		{
			String_ += ssChar;
			Font_->GameContentChangeFont(String_, { 0,0 });
		}
	}




	for (char c = '0'; c <= '9'; ++c)
	{
		std::string ssChar;
		ssChar += c;

		if (GameEngineInput::GetInst()->IsDown("ChatKey" + ssChar))
		{
			String_ += ssChar;
			Font_->GameContentChangeFont(String_, { 0,0 });
		}
	}


	if (GameEngineInput::GetInst()->IsDown("EnterChat") && String_.size() > 0)
	{
		ChatBox* chatBox = dynamic_cast<ChatBox*>(GetLevel()->FindActor("ChatBox"));
		chatBox->CreateChatList(String_);
		String_ = "";
		Font_->GameContentChangeFont(String_, { 0,0 });
	}


	if (GameEngineInput::GetInst()->IsDown("BackSpace") && String_.size() > 0)
	{
		String_.pop_back();
		Font_->GameContentChangeFont(String_, { 0,0 });

	}


	if (GameEngineInput::GetInst()->IsDown("ChatKeyGrave_Empty"))
	{
		String_ += " ";
		Font_->GameContentChangeFont(String_, { 0,0 });

	}	
}
