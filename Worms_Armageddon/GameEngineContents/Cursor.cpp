#include "Cursor.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

const float CursorImgScale = 2.0f;
const float CursorImgPivot_X = 16.0f;
const float CursorImgPivot_Y = 16.0f;

Cursor::Cursor() 
{
}

Cursor::~Cursor() 
{
}

void Cursor::Start()
{
	// 마우스 이미지 설정
	Renderer_ = CreateRenderer("Cursor.bmp", static_cast<int>(RenderOrder::Cursor));
	Renderer_->SetScale(Renderer_->GetScale() * CursorImgScale);
	Renderer_->SetPivot(float4{ CursorImgPivot_X, CursorImgPivot_Y });

	// 기존 커서 감추기
	ShowCursor(false);

	// 마우스 가운데 버튼
	if (false == GameEngineInput::GetInst()->IsKey("MouseDebugSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("MouseDebugSwitch", VK_MBUTTON);
	}
}

void Cursor::Update()
{
	CursorUpdate();
	
}

void Cursor::Render()
{
	CursorDebugRender();
}

void Cursor::CursorUpdate()
{
	//마우스 관련 함수
	GetCursorPos(&MousePos_);
	ScreenToClient(GameEngineWindow::GetHWND(), &MousePos_);
	CursorPos_.x = static_cast<float>(MousePos_.x);
	CursorPos_.y = static_cast<float>(MousePos_.y);

	SetPosition(CursorPos_);
}


void Cursor::CursorDebugRender()
{
	TCHAR szBuff[64] = "";

	sprintf_s(szBuff, "Mouse X: %d, Y: %d", CursorPos_.ix(), CursorPos_.iy());
	TextOut(GameEngine::GetInst().BackBufferDC(), CursorPos_.ix() + 20, CursorPos_.iy() - 20, szBuff, static_cast<int>(strlen(szBuff)));

}