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
	Font,
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

enum class LevelFSM
{
	// 모든 페이즈에서 플레이어 웜즈가 데미지를 받을 경우 턴이 종료됨

	Ready,		 // 입력전의 준비단계, 제한시간이 흐르지않음. 
				 //입력이 없을경우 자동으로 5초뒤에 다음 페이즈로 넘어감

	Move,		 // 이동 단계, 이동, 조준, 무기 변경을 함
	WeaponShoot, // 무기발사 페이즈, 플레이어 웜즈가 공격을 했을경우
				 // 공격을 받은 웜즈의 움직임이 멈춘 후 5초뒤까지 이동이 가능?

	Damage,		 // 데미지 계산,

	// 반복
	Death,		 // 죽은 캐릭터가 있으면 카메라 이동 및 자폭공격
	DeathDamage, // 자폭공격에 맞았으면 데미지 계산
	// 반복

	// 데미지 끝남
	TurnEnd,	 // 바람이 바뀜, 보급이 내려오고, 기타등등
	// -> Ready
};