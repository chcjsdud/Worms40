#pragma once
#include "Enums.h"
#include "WeaponMaster.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>

// 설명 :
class GameEngineImage;
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
private:
	// 속도
	float Speed_;
	// 낙하 속도
	float FallSpeed_;
	// 낙하 거리
	float FallLength_;

	// 플레이어 Hp
	int PlayerHp_;

	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;
	// 카메라의 위치
	float4 CameraPos_;
	// 사운드 오브젝트
	GameEngineSound* SoundPlayer_;

	// 플레이어 렌더러
	GameEngineRenderer* PlayerRenderer_;

	// 플레이어가 충돌처리를 할 맵 이미지
	GameEngineImage* ColMapImage_;

	// 플레이어가 들고 있는 무기의 타입
	int WeaponType_;
	// 생성할 무기
	WeaponMaster* Weapon_;

	std::string DirName_;
	std::string StateName_;

	// 현재 레벨
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// 애니메이션 초기화
	void PlayerAnimationInit();
	// 키 초기화
	void PlayerKeyInit();
	// 카메라 업데이트
	void UpdateCamera();

	// 키입력 관련 함수
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();

	// 이동중 충돌체크
	void MoveCheck(float4 _MoveDir);
	void MoveFall();
	//오르막길 픽셀충돌체크
	void CheckHillPixel();
	// FSM
public:
	// 상태전환
	void StateChange(PlayerState _State);
	// 상태 업데이트
	void StateUpdate();
private:
	// 현재 상태
	PlayerState CurrentState_;

	void IdleStart();
	void MoveStart();
	void ActionStart();
	void JumpStart();

	void IdleUpdate();
	void MoveUpdate();
	void ActionUpdate();
	void JumpUpdate();

	void PlayerAnimationChange(std::string _Anim);
	
};

