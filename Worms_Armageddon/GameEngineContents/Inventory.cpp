#include "Inventory.h"
#include "Enums.h"
#include "Cursor.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

const int InventoryHegiht = 11;
const int InventoryWidth = 5;

Inventory::Inventory() 
	: IsOut_(false)
{
	WeaponButtons_.resize(InventoryHegiht, std::vector<GameEngineCollision*>(InventoryWidth, nullptr));
}

Inventory::~Inventory() 
{

}

void Inventory::Start()
{
	GridRenderer_ = CreateRenderer("WeaponSheet_Empty.bmp", (int)RenderOrder::UI);
	GridRenderer_->SetPivot(GridRenderer_->GetScale().Half());
	GridRenderer_->CameraEffectOff();

	// In Out 위치 설정
	SetPosition({ 1300.0f, 500.0f });
	OutPos_ = GetPosition();
	InPos_ = GetPosition() + float4{ -210, 0 };

	// 5 x 11 아이템 목록
	float ColPaddingX = 45.0f;
	float ColPaddingY = 16.0f;
	for (int y = 0; y < InventoryHegiht; y++)
	{
		for (int x = 0; x < InventoryWidth; x++)
		{
			GameEngineCollision* ptr = CreateCollision("Button", { 27, 27 }, { ColPaddingX + x * 29.0f, ColPaddingY + y * 29.0f });
			ptr->CameraEffectOff();
			WeaponButtons_[y][x] = ptr;
		}
	}
}

void Inventory::Update()
{
	UpdateState();
	MoveInOut();
	ClickWeapon();
}

void Inventory::MoveInOut()
{
	// 인벤토리 In <-> Out
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_RIGHT))
	{
		if (IsOut_ == false)
		{
			MoveSetting(OutPos_, InPos_, 800.0f);
			IsOut_ = !IsOut_;
		}
		else
		{
			MoveSetting(InPos_, OutPos_, 800.0f);
			IsOut_ = !IsOut_;
		}

		Move();

	}
}

void Inventory::ClickWeapon()
{
	// 클릭 체크
	{
		if (false == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
		{
			return;
		}

		float4 CursorPos = Cursor::GetCursorPosition();
		float4 LeftTop = InPos_;
		float4 RightBottom = InPos_ + GridRenderer_->GetScale();

		// 인벤토리UI 바깥 클릭
		if (CursorPos.x < LeftTop.x && CursorPos.y < LeftTop.y ||
			CursorPos.x > RightBottom.x && CursorPos.y > RightBottom.y)
		{
			return;
		}
	}

	// 어느 무기인지 체크
	int IdxX = 0;
	int IdxY = 0;
	for (int y = 0; y < InventoryHegiht; y++)
	{
		for (int x = 0; x < InventoryWidth; x++)
		{
			if (WeaponButtons_[y][x]->CollisionCheck(COL_GROUP_MOUSE))
			{
				IdxX = x;
				IdxY = y;
				break;
			}
		}
	}

	int a = 0;
}
