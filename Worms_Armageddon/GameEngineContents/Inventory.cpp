#include "Inventory.h"
#include "Cursor.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

const int InventoryHegiht = 11;
const int InventoryWidth = 5;
const float SlotPaddingX = 45.0f;
const float SlotPaddingY = 16.0f;
const float SlotSpeed = 3000.0f;

Inventory::Inventory() 
	: IsOut_(false)
	, ClickedWeapon_(WeaponState::None)
	, GridRenderer_(nullptr)
{
	WeaponButtons_.resize(InventoryHegiht, std::vector<InventoryButton>(InventoryWidth, InventoryButton()));
}

Inventory::~Inventory()
{
}

void Inventory::Start()
{
	GridRenderer_ = CreateRenderer("WeaponSheet_Full.bmp", (int)RenderOrder::UI);
	GridRenderer_->SetPivot(GridRenderer_->GetScale().Half());
	GridRenderer_->CameraEffectOff();

	// In Out ��ġ ����
	SetPosition({ 1300.0f, 590.0f });
	OutPos_ = GetPosition();
	InPos_ = GetPosition() + float4{ -210, 0 };

	// 5 x 11 ���� ��� �ʱ�ȭ
	for (int y = 0; y < InventoryHegiht; y++)
	{
		for (int x = 0; x < InventoryWidth; x++)
		{
			// Collision ����
			{
				WeaponButtons_[y][x].Col_ = CreateCollision("Button", { 27, 27 }, { SlotPaddingX + x * 29.0f, SlotPaddingY + y * 29.0f });
				WeaponButtons_[y][x].Col_->CameraEffectOff();
			}

			// Renderer ����
			{
				WeaponButtons_[y][x].WeaponSelector_ = CreateRenderer("WeaponSelector.bmp", (int)RenderOrder::UI);
				WeaponButtons_[y][x].WeaponSelector_->SetScale({ 27, 27 });
				WeaponButtons_[y][x].WeaponSelector_->SetPivot({ SlotPaddingX + x * 29.0f, SlotPaddingY + y * 29.0f });
				WeaponButtons_[y][x].WeaponSelector_->CameraEffectOff();
				WeaponButtons_[y][x].WeaponSelector_->SetTransColor(RGB(0, 0, 0));
				WeaponButtons_[y][x].WeaponSelector_->Off();
			}
		}
	}

	InventoryWeaponInit();
}

void Inventory::Update()
{
	UpdateState();
	MoveInOut();
	OnOffSelector();
	ClickWeapon();
}

void Inventory::MoveInOut()
{
	// �κ��丮 In <-> Out
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_RIGHT))
	{
		if (IsOut_ == false)
		{
			UIMaster::MoveSetting(OutPos_, InPos_, SlotSpeed);
			IsOut_ = !IsOut_;
		}
		else
		{
			UIMaster::MoveSetting(InPos_, OutPos_, SlotSpeed);
			IsOut_ = !IsOut_;
		}

		UIMaster::Move();

	}
}

void Inventory::ClickWeapon()
{
	// ��Ŭ�� üũ
	if (false == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT))
	{
		ClickedWeapon_ = WeaponState::None;
		return;
	}

	float4 CursorPos = Cursor::GetCursorPosition();
	float4 LeftTop = InPos_;
	float4 RightBottom = InPos_ + GridRenderer_->GetScale();

	// �κ��丮UI �ٱ� Ŭ��
	if (false == (CursorPos.x >= LeftTop.x && CursorPos.x <= RightBottom.x &&
		CursorPos.y >= LeftTop.y && CursorPos.y <= RightBottom.y) )
	{
		ClickedWeapon_ = WeaponState::None;
		return;
	}

	// ��� �������� üũ
	int IdxX = 0;
	int IdxY = 0;
	for (int y = 0; y < InventoryHegiht; y++)
	{
		for (int x = 0; x < InventoryWidth; x++)
		{
			if (WeaponButtons_[y][x].Col_->CollisionCheck(COL_GROUP_MOUSE))
			{
				ClickedWeapon_ = WeaponButtons_[y][x].Weapon_;
				break;
			}
		}
	}

	// Ŭ���ϸ� �κ��丮 ����ֱ�
	if (true == IsOut_)
	{
		IsOut_ = false;
		UIMaster::MoveSetting(InPos_, OutPos_, SlotSpeed);
		UIMaster::Move();
	}
}

// ���� ���� Ŀ�� �ö󰡸� ��輱 On/Off
void Inventory::OnOffSelector()
{
	for (int y = 0; y < InventoryHegiht; y++)
	{
		for (int x = 0; x < InventoryWidth; x++)
		{
			if (false == WeaponButtons_[y][x].Col_->CollisionCheck(COL_GROUP_MOUSE))
			{
				WeaponButtons_[y][x].WeaponSelector_->Off();
			}
			else
			{
				WeaponButtons_[y][x].WeaponSelector_->On();
			}
		}
	}
}

// �κ��丮 ����� �������� �ʱ�ȭ
void Inventory::InventoryWeaponInit()
{
	WeaponButtons_[1][0].Weapon_ = WeaponState::Baz;
	WeaponButtons_[2][0].Weapon_ = WeaponState::Grenade;
	WeaponButtons_[6][0].Weapon_ = WeaponState::AirStrike;
	WeaponButtons_[5][2].Weapon_ = WeaponState::Sheep;
	WeaponButtons_[5][3].Weapon_ = WeaponState::SuperSheep;
}