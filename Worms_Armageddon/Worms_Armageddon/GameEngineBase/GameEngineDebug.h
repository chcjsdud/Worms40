#pragma once
#include <crtdbg.h>
#include <string>
#include <assert.h>
#include <Windows.h>

// 설명 :
class GameEngineDebug
{
public:
	static void LeakCheckOn();

	// 보기 좋은 안전한 함수.
	// static void MsgBoxAssert(const std::string& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

};

#define MsgBoxAssert(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, Text, "Error", MB_OK); \
assert(false); 

#define MsgBoxAssertString(Text) 	MessageBeep(0); \
MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK); \
assert(false); 
