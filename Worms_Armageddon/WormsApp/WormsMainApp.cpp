#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/Worms.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineMath.h>


int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char* lpCmdLine,
    _In_ int       nCmdShow)
{
 
    //leak È®ÀÎ¿ë
    new int();

    GameEngine::Start<Worms>();

} 