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
	WeaponSwap,
	Move,
	Jump,
	BackFlip,
	Falled,
	Action,
	FlyAway,
	Death,
	Slide,
	None
};

enum class PlayerUnControlState
{
	UncontrolIdle,
	FlyAway
};



enum class RenderOrder
{
	// ���
	BackGround_0,

	PlayStar,

	// ���� ��Ÿ���
	BackGround_1,
	// ��
	BackGround_2,
	Back_Fx,
	Weapon,
	// ��
	BackGround_3,

	LobbyStar,

	Player,
	Front_Fx,
	UI,
	UI_2,
	SelectBox,
	HpBar,
	Font,
	Cursor,
};

enum class WeaponState
{
	//Throw ���� ���� ������
	// ������� �� ���� �ٿ��ֱ� (���ڷ� ����)
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
	SuperSheep,

	// F6
	AirStrike,

	// F7
	BlowTorch,
	Drill,
	Grider,

	// F8

	// F9

	// F10

	// F11

	// F12


	None
};

// ��Ÿ��
enum class MapType
{
	Birthday,
	Books,
	Other,
};


enum class WindType
{
	Left,
	Right
};

enum class LevelFSM
{
	// ��� ������� �÷��̾� ��� �������� ���� ��� ���� �����

	Ready,		 // �Է����� �غ�ܰ�, ���ѽð��� �帣������. 
				 //�Է��� ������� �ڵ����� 5�ʵڿ� ���� ������� �Ѿ

	Move,		 // �̵� �ܰ�, �̵�, ����, ���� ������ ��
	CameraMove,	 // �������� ���� �÷��̾�� ī�޶� �̵�

	Damage,		 // ������ ���,
	SetDamagePlayer, // ������ ���� �÷��̾� ����, ī�޶� �̵� ��

	Death,		 // ���� ĳ���Ͱ� ������ ī�޶� �̵� �� ��������

	TurnEnd,	 // �ٶ��� �ٲ�, ������ ��������, ��Ÿ���
	// -> Ready
};

enum class TeamColor
{
	Red,
	Blue,
	Green,
	Yellow,
	Pink,
	Mint,
	Max,
};

enum class FxPlayList
{
	Foom,
	Circle50,
	Elipse50,
	SupersheepSkid
};

enum class CreateEffect
{
	Foom
};


//�ȼ��浹�� ��� Ÿ��
enum class CheckType
{
	None,
	Player,
	WeaponMissile,
	WeaponGrenade
};