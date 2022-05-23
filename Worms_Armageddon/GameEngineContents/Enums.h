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
	// 배경
	BackGround_0,
	// 물과 기타등등
	BackGround_1,
	// 맵
	BackGround_2,
	// 맵
	BackGround_3,

	Weapon,
	Player,
	UI,
	Cursor,
};

enum class WeaponState
{
	//Throw 상태 별도 존재함

	// F1
	Baz,
	Homing,
	Mortar,

	// F2
	Grn,
	
	Axe,

	// F3


	Uzi,

	// F4
	FirePunch,

	// F5


	Sheep,

	// F6
	AirStrike,

	// F7
	BlowTorch,
	Drill,
	Grider

	// F8

	// F9

	// F10

	// F11

	// F12
};

// 맵타입
enum class MapType
{
	Birthday,
	Books,

};


enum class WindType
{
	Left,
	Right
};