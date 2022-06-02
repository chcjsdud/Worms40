#include "Cursor.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

const float CursorImgScale = 2.0f;
const float CursorImgPivot_X = 16.0f;
const float CursorImgPivot_Y = 16.0f;
float4 Cursor::CursorPos_ = float4{ 0, 0 };

Cursor::Cursor() 
	: IsDebugMode_(false)
	, MousePos_(POINT())
	, Renderer_(nullptr)
	, Collision_(nullptr)
{
}

Cursor::~Cursor() 
{
}

void Cursor::Start()
{
	// 마우스 이미지 설정
	Renderer_ = CreateRenderer(IMG_MOUSE_CURSOR, static_cast<int>(RenderOrder::Cursor));
	Renderer_->SetScale(Renderer_->GetScale() * CursorImgScale);
	Renderer_->SetPivot(float4{ CursorImgPivot_X, CursorImgPivot_Y });
	Renderer_->CameraEffectOff();

	// 마우스 충돌체
	Collision_ = CreateCollision(COL_GROUP_MOUSE, {1, 1});
	Collision_->CameraEffectOff();

	// 기존 커서 감추기
	ShowCursor(false);

	// 마우스 가운데 버튼
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOUSE_MID))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_MID, VK_MBUTTON);
	}
}

void Cursor::Update()
{
	CursorUpdate();
	
}

void Cursor::Render()
{
	if (true == IsDebugMode_)
	{
		CursorDebugRender();
	}
}

void Cursor::CursorUpdate()
{
	SetCursorPos();
	SetPosition(CursorPos_);

	DebugMode();
}

void Cursor::SetCursorPos()
{
	GetCursorPos(&MousePos_);
	ScreenToClient(GameEngineWindow::GetHWND(), &MousePos_);
	CursorPos_.x = static_cast<float>(MousePos_.x);
	CursorPos_.y = static_cast<float>(MousePos_.y);
}


void Cursor::CursorDebugRender()
{
	TCHAR szBuff[64] = "";

	sprintf_s(szBuff, "Mouse X: %d, Y: %d", CursorPos_.ix(), CursorPos_.iy());
	TextOut(GameEngine::GetInst().BackBufferDC(), CursorPos_.ix() + 20, CursorPos_.iy() - 20, szBuff, static_cast<int>(strlen(szBuff)));
}

void Cursor::DebugMode()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_MID))
	{
		IsDebugMode_ = !IsDebugMode_;
		GetLevel()->IsDebugModeSwitch();
	}
}
