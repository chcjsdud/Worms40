#pragma once
#include "Enums.h"
#include "GameMapMaster.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

// 설명 : 
class GameEngineImage;
class GameEngineRenderer;
class PixelCollision;
class WeaponMaster :public GameEngineActor
{
public:
	// constrcuter destructer
	WeaponMaster();
	~WeaponMaster();

	// delete Function
	WeaponMaster(const WeaponMaster& _Other) = delete;
	WeaponMaster(WeaponMaster&& _Other) noexcept = delete;
	WeaponMaster& operator=(const WeaponMaster& _Other) = delete;
	WeaponMaster& operator=(WeaponMaster&& _Other) noexcept = delete;

	virtual bool WeaponUpdate() 
	{ 
		return true;
	}

	static inline void SetGameMap(GameMapMaster* _GameMap)
	{
		GameMap_ = _GameMap;
	}

	static inline GameMapMaster* GetGameMap()
	{
		return GameMap_;
	}

	virtual float4 GetWeaponPosition()
	{
		return GetPosition();
	}

	inline void SetShotAngle(float4 _ShotAngle)
	{
		ShotAngle_ = _ShotAngle;
	}

	inline void SetShotPower(float _ShotPower)
	{
		ShotPower_ = _ShotPower;
	}

	inline bool GetExplodEndFlg() const
	{
		return IsExplodEnd_;
	}

private: 
	// 지정한 목표 좌표
	float4 TargetPos_;
	// 무기가 발사 되는순간 최초 실행
	bool Shot_;
	bool IsShot_;
	// 투하하는 순간 최초 실행
	bool IsDrop_;
	// 바운스 투사체를 굴리기 위한 회전값
	float BounceRotate_;
	bool IsBomb_;

	// 무기의 폭발이 끝나는 플래그
	bool IsExplodEnd_;

	// 레벨이 시작함과 동시에 초기화될 맵 정보
	// static으로 설정하여 모든 무기가 공유하도록 함
	static GameMapMaster* GameMap_;

	// 바람 방향 정보
	float4 WindInfo_;
	// 투사체가 자식 투사체를 생성한 횟수
	int BombCnt_;

	// 투사체 투하 : 어떤 것을 투하할지 지정, 투하시간 간격
	void Drop(WeaponState _Drop, float _Sec = 0);

protected:
	// 무기 랜더
	GameEngineRenderer* WeaponRender_;
	//튕기는 무기인지 아닌지 체크해주는 변수
	bool IsBounce_;
	// 무기 발사 방향
	float4 ShotDir_;
	PixelCollision* PixelCol_;
	// 투사체의 방향
	float4 BulletDir_;
	// 무기 발사각도
	float4 ShotAngle_;
	// 무기 발사 힘
	float ShotPower_;

	// 카메라가 봐야할 무기의 위치
	// 기본적으로는 GetPosition(), 폭격기등의 투사체가 많을경우에만 특수하게 설정
	static float4 WeaponCameraPos_;

	static bool WeaponStaticReturn_;

	void Start() override;
	void Update() override;

	// 투사체 투척용 함수 : 포스값의 강도로 날림
	void ThrowStart(float _ThrowForce);
	// 폭격기 출격 : 폭격기가 어디서 생성될지 지정
	void AirStart(float4 _AirSpawn);
	// 목표 좌표 지정
	void TargetCursor();

	// 투사체 움직임 연산 : 중력값만 넣어주면 포물선으로 날아감
	void BulletMove(float _Gravity, bool _IsWind);
	// 폭격 폭탄 투하 : 어느 폭탄을 투하할지 지정
	bool Bombing(WeaponState _Bomb);

	// 투사체 충돌 시 발생 이벤트
	bool BulletColEvent();
	// 폭발 (맵을 파고 폭발 이펙트생기고 투사체 제거)
	void Explosion();

public:
	inline void SetShotDir(float4 _WeaponDir)
	{
		ShotDir_ = _WeaponDir;
	}
};

