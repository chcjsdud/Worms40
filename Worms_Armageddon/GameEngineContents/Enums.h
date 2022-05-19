#pragma once


enum class ActorGroup
{
	BackGround,
	Player,
	UI,
};

enum class PlayerState
{
	Idle,
	Move,
	Action
};

enum class RenderOrder
{
	BackGround_0,
	BackGround_1,
	BackGround_2,
	Weapon,
	Player,
	UI,
	Cursor,
};

enum class WeaponState
{
	Baz
};

// ∏ ≈∏¿‘
enum class MapType
{
	MAPBOOKS,
};


enum class WindType
{
	Left,
	Right
};