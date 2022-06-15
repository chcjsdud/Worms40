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
	// 배경
	BackGround_0,

	PlayStar,

	// 물과 기타등등
	BackGround_1,
	// 맵
	BackGround_2,
	Back_Fx,
	Weapon,
	// 맵
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
	//Throw 상태 별도 존재함
	// 기모으는 것 끼리 붙여넣기 (숫자로 관리)
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

// 맵타입
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
	// 모든 페이즈에서 플레이어 웜즈가 데미지를 받을 경우 턴이 종료됨

	Ready,		 // 입력전의 준비단계, 제한시간이 흐르지않음. 
				 //입력이 없을경우 자동으로 5초뒤에 다음 페이즈로 넘어감

	Move,		 // 이동 단계, 이동, 조준, 무기 변경을 함
	CameraMove,	 // 턴종료후 다음 플레이어로 카메라 이동

	Damage,		 // 데미지 계산,
	SetDamagePlayer, // 데미지 받은 플레이어 설정, 카메라 이동 등

	Death,		 // 죽은 캐릭터가 있으면 카메라 이동 및 자폭공격

	TurnEnd,	 // 바람이 바뀜, 보급이 내려오고, 기타등등
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


//픽셀충돌할 대상 타입
enum class CheckType
{
	None,
	Player,
	WeaponMissile,
	WeaponGrenade
};