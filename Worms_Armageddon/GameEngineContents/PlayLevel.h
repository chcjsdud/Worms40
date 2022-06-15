#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngineBase/GameEngineSound.h>

#include "Cursor.h"
#include "WindGauge.h"
#include "PlayShootingStar.h"

// 설명 :
class WeaponMaster;
class GameMapMaster;
class Player;
class GameEngineRenderer;
class GameEngineImage;
class UIMaster;
class TeamHpBarList;
class TimerActor;
class PlayLevel	:public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameMapMaster* GameMapInfo_;

	WeaponMaster* WeaponMaster_;
	Cursor* Mouse_;
	WindGauge* WindGaugeActor_;
	UIMaster* InventoryActor_;
	TeamHpBarList* TeamHpBarListActor_;

	// Lerp처리시 시작할 카메라 위치
	float4 LerpStartCameraPos_;
	// 가장 최근의 무기의 위치
	float4 CurrentWeaponPos_;

	// 데미지 받은 캐릭터로 카메라가 이동할때 딜레이 타이머
	TimerActor* DamagedCharCameraDelayTimer_;

	float4 WindDir_;
	float WindSpeed_;

	Player* Player_[PLAYER_MAX_TEAM][PLAYER_MAX_NUMBER];
	std::map<TeamColor, int> PlayerColorTeamSetting_;

	std::list<std::list<Player*>>::iterator AllPlayerIter_;
	std::list<std::list<Player*>> AllPlayer_;
	std::list<std::list<Player*>> PlayQueue_;
	std::list<Player*> DeathList_;
	Player* TargetPlayer_;

	// 현재 페이즈
	LevelFSM LevelPhase_;
	// 직전 페이즈
	LevelFSM PrevPhase_;


	// 카메라 업데이트
	void UpdateCamera(float4 _CameraPos);
	// 카메라의 위치
	float4 CameraPos_;
	// 카메라 이동용 이전 플레이어 위치
	float4 PrevPlayerPos_;
	// 마우스로 카메라 조작용 이전 마우스 위치
	float4 PrevCameraPos_;
	// 마우스로 카메라를 이동하는 플래그
	// false = 마우스로 조작하지 않음, true = 마우스로 조작함
	bool CameraControledByWASDFlg_;
	// 다음 플레이어 위치
	float4 NextPlayerPos_;
	float4 NextDamagedPlayerPos_;
	// 보간처리용 타이머
	float LerpTimer_;
	//별
	PlayShootingStar* PlayShootingStar_;

	// 에어스트라이크류 공격에 대한 공격처리
	void PlayerDamagedCheck4AirStrike();
	void PlayerDamagedCheck4NormalWeapon();

	/// UI ///
	// 바람
	void SetWindUI(int _WindDir);

	GameEngineSoundPlayer SoundPlayer_BGM_;
	GameEngineSoundPlayer SoundPlayer_Hello_;

public:
	float4 GetWindDir()
	{
		return WindDir_;
	}

	Cursor* GetCursor()
	{
		return Mouse_;
	}

	float4 GetCameraPos()
	{
		return CameraPos_;
	}
};

