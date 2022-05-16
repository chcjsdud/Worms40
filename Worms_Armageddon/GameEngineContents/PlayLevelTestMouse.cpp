#include "PlayLevelTestMouse.h"
#include <GameEngineBase/GameEngineRandom.h>
#include<GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>


PlayLevelTestMouse::PlayLevelTestMouse() 
{

}

PlayLevelTestMouse::~PlayLevelTestMouse() 
{

}

void PlayLevelTestMouse::Start()
{
	/*BulletRenderer_ = CreateRenderer();
	BulletRenderer_->SetImage("Armageddon_9.bmp");*/


}

void PlayLevelTestMouse::Update()
{
	//마우스 업데이트
	MouseUpdate();



}

void PlayLevelTestMouse::Render()
{
	MouseDebugRender();
}


void PlayLevelTestMouse::MouseUpdate()
{
	//마우스 관련 함수
	GetCursorPos(&Mouse_);
	ScreenToClient(GameEngineWindow::GetHWND(), &Mouse_);
	CursorPos_.x = static_cast<float>(Mouse_.x);
	CursorPos_.y = static_cast<float>(Mouse_.y);

	SetPosition(CursorPos_);

}

void PlayLevelTestMouse::MouseDebugRender()
{
	TCHAR szBuff[64] = "";

	sprintf_s(szBuff, "Mouse X: %d, Y: %d", CursorPos_.ix(), CursorPos_.iy());
	TextOut(GameEngine::GetInst().BackBufferDC(), CursorPos_.ix()+20, CursorPos_.iy()-20, szBuff, static_cast<int>(strlen(szBuff)));

}
