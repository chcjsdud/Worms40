#include "GameEngineDebug.h"



GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

//void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
//{
//	MessageBeep(0); 
//	MessageBoxA(nullptr, _Text.c_str(), "Error", MB_OK); 
//	assert(false);
//	// 그냥 자기자신으로 띄웁니다.
//	// 윈도우 핸들 넣어달라고 합니다
//	// 니가 만든거면
//	// 안넣어주면 알아서 window를 하나 만들어준다.
//	
//	
//}