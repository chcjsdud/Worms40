#pragma once
#include "Enums.h"
#include "WeaponMaster.h"
#include "HpBar.h"
#include "Crosshair.h"
#include "ChargeBlob.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

// 설명 :
class GameEngineImage;
class PixelCollision;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

	// 게임 초기 설정
public:
	inline void SetPlayerHp(int _WormzHp)
	{
		PlayerHp_ = _WormzHp;

	}

	inline bool GetIsDamagedCam() const
	{
		return IsDamagedCam_;
	}

	inline void SetIsDamagedCam(bool _IsDamagedCam)
	{
		IsDamagedCam_ = _IsDamagedCam;
	}

	inline int GetPlayerHp()
	{
		return PlayerHp_;
	}

	inline bool GetIsDeath()
	{
		return IsDeath_;
	}

	inline bool GetIsTurnEnd()
	{
		return IsTurnEnd_;
	}

	PlayerState GetPlayerState() const
	{
		return CurrentState_;
	}

	float4 GetWeaponPos() const
	{
		return WeaponPos_;
	}

	inline void SetMyTeamColor(TeamColor _Color)
	{
		MyTeamColor_ = _Color;
		SetFontColor(static_cast<FONT_COLOR>(_Color));
	}


	inline void SetControlFlg(bool _ControlFlg)
	{
		ControlFlg_ = _ControlFlg;
	}

	inline void SetTurnEndFlg(bool _TurnEndFlg)
	{
		IsTurnEnd_ = _TurnEndFlg;
	}


	bool ControllUpdate();


	//데미지 체크
	void Damaged(float4 _WeaponPos = float4::ZERO);
private:

	float FlySpeed_;

	bool IsTurnEnd_;
	
	//데미지를 입었냐 안입었냐 확인하는 flag
	bool IsDamaged_;
	bool IsDamagedCam_;
	//모든 데미지의 총합
	int AllDamage_;
	int Damage_;
	// 속도
	float Speed_;
	// 낙하 속도
	float FallSpeed_;
	float SlideFallspeed_;
	// 낙하 거리
	float FallLength_;
	//점프 속도
	float JumpSpeed_;
	//점프사전준비동작 애니메이션 플레이타임
	float JumpDelayTime_;
	// 무기 상태
	WeaponState WeaponState_;
	WeaponState PrevWeaponState_;
	// 무기 위치
	float4 WeaponPos_;
	// 폭발한 무기의 위치
	float4 ExplodWeaponPos_;
	// 픽셀 체크
	PixelCollision* PixelCol_;
	// 플레이어 Hp
	int PlayerHp_;

	bool IsGrave_;

	// 나의 팀 색깔 정보
	TeamColor MyTeamColor_;

	// 무기 발사각도
	float4 ShotAngle_;
	float4 ShotAngleMax_;
	float4 ShotAngleMin_;

	// 무기 발사 힘
	float ShotPower_;

	//무기와 플레이어 사이의 거리
	float Len_;

	// 플레이어 사망 플래그
	bool IsDeath_;

	bool IsJump_;
	//무기 바꾸는 애니메이션 체크용
	bool IsSwitch;

	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;
	//점프중 좌우방향
	float4 JumpMoveDir_;
	//날라가는 방향
	float4 FlyMoveDir_;

	// 사운드 오브젝트
	GameEngineSoundPlayer Sound_Walk;
	GameEngineSoundPlayer Sound_Fall;
	GameEngineSoundPlayer Sound_Jump;
	GameEngineSoundPlayer Sound_Backflip;
	GameEngineSoundPlayer Sound_Byebye;
	bool Sound_JumpOn;
	bool Sound_BackflipOn;

	static GameEngineRandom Ran;

	// 플레이어 렌더러
	GameEngineRenderer* PlayerRenderer_;

	// 플레이어가 충돌처리를 할 맵 이미지
	GameEngineImage* ColMapImage_;

	// 플레이어가 들고 있는 무기의 타입
	int WeaponType_;
	// 생성할 무기
	static WeaponMaster* Weapon_;

	// HpBar
	HpBar* Hpbar_;

	// 행동중 화살표 렌더러
	GameEngineRenderer* ControlWorms_;

	// Crosshair
	Crosshair* Crshair_;

	// ChargeBlob
	ChargeBlob* CrgBlob_;

	//애니메이션용 방향이름
	std::string DirName_;
	std::string StateName_;
	std::string CurDirName_;

	// 현재 레벨
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}


	// 애니메이션 초기화
	void PlayerAnimationInit();
	// 키 초기화
	void PlayerKeyInit();
	//플레이어 죽음 처리함수
	void CheckDeath();


	bool ControlFlg_;
	float DeathDelayTime_;
	bool SlideEnd_;
	bool IsFly_;

	//키 입력 카운트
	int KeyCount_;

	//키 입력 타이머 ,  더블클릭용
	float KeyTimer_;

	// 키입력 관련 함수
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();
	bool IsJumpKeyDown();
	bool IsBackFlipKeyDown();
	bool IsBackFlipKeyFree();
	bool IsPlayerDeathKeyDown();



	// 이동중 충돌체크
	void MoveCheck(float4 _MoveDir);
	// 중력
	void MoveFall();
	//오르막길 픽셀충돌체크
	void CheckHillPixel();
public:
	// 상태전환
	void StateChange(PlayerState _State);
	// 상태 업데이트
	void StateUpdate();
	void FlyAwayStart();
private:
	// 현재 상태
	PlayerState CurrentState_;
	// 이전 상태
	PlayerState PrevState_;

	//
	PlayerUnControlState UnControlState_;

	void IdleStart();
	void WeaponSwapStart();
	void MoveStart();
	void ActionStart();
	void JumpStart();
	void BackFlipStart();
	void FalledStart();
	void DeathStart();
	void SlideStart();



	void IdleUpdate();
	void WeaponSwapUpdate();
	void MoveUpdate();
	void ActionUpdate();
	void JumpUpdate();
	void BackFlipUpdate();
	void FalledUpdate();
	void FlyAwayUpdate();
	void DeathUpdate();
	void SlideUpdate();

	void PlayerAnimationChange(std::string _Anim);

	//HPBar
	void SetFontColor(FONT_COLOR _Color);

public:
	void ChangeHpBarFont(int _Hp);			//폰트 체인지
	void CreateHpBar(int _Hp, float4 _Pivot,  FONT_COLOR _Color);
	void CreateControlArrow(TeamColor _TeamColor);
	
	void MoveWeaponAngle(float _DeltaTime);
	void ChargingWeaponPower();
};

