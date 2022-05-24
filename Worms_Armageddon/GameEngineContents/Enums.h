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
	Jump,
	Action
};

enum class RenderOrder
{
	// ���
	BackGround_0,
	// ���� ��Ÿ���
	BackGround_1,
	// ��
	BackGround_2,
	// ��
	BackGround_3,

	Weapon,
	Player,
	UI,
	Font,
	Cursor,
};

enum class WeaponState
{
	//Throw ���� ���� ������

	// F1
	Baz,
	Homing,
	Mortar,

	// F2
	Grenade, // Grn
	
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

// ��Ÿ��
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