#include "TitleLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{

}

void TitleLevel::Loading()
{
	// 디버그용
	if (false == GameEngineInput::GetInst()->IsKey("MoveTitleLevel"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveTitleLevel", '1');
		GameEngineInput::GetInst()->CreateKey("MovePlayLevel", '2');
	}
}

void TitleLevel::Update()
{
	// 디버그용
	if (GameEngineInput::GetInst()->IsDown("MoveTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
	if (GameEngineInput::GetInst()->IsDown("MovePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}
}

