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
	// πË∞Ê
	BackGround_0,
	// π∞∞˙ ±‚≈∏µÓµÓ
	BackGround_1,
	// ∏ 
	BackGround_2,
	// ∏ 
	BackGround_3,

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