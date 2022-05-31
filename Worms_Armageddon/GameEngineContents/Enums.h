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
	BackFlip,
	Falled,
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

	LobbyStar,

	Back_Fx,
	Weapon,
	Player,
	Front_Fx,
	UI,
	SelectBox,
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
	CameraMove, 
	Damage,		 // ������ ���,

	// �ݺ�
	Death,		 // ���� ĳ���Ͱ� ������ ī�޶� �̵� �� ��������
	DeathDamage, // �������ݿ� �¾����� ������ ���
	// �ݺ�

	// ������ ����
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
	Elipse50
};

enum class CreateEffect
{
	Foom
};