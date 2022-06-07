#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "LargeCloud.h"
#include "Cursor.h"
#include "WindGauge.h"
#include "SmallCloud.h"
#include "Water.h"

// 설명 :
class WeaponMaster;
class GameMapMaster;
class Player;
class GameEngineRenderer;
class GameEngineImage;
class UIMaster;
class TeamHpBarList;
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
	LargeCloud* LargeCloudActor_;
	SmallCloud* SmallCloudActor_;

	Water* WaterActor_;
	WeaponMaster* WeaponMaster_;
	Cursor* Mouse_;
	WindGauge* WindGaugeActor_;
	UIMaster* InventoryActor_;
	TeamHpBarList* TeamHpBarListActor_;

	// Lerp처리시 시작할 카메라 위치
	float4 LerpStartCameraPos_;
	// 가장 최근의 무기의 위치
	float4 CurrentWeaponPos_;

	float4 WindDir_;
	float WindSpeed_;

	Player* Player_[PLAYER_MAX_TEAM][PLAYER_MAX_NUMBER];
	std::map<TeamColor, int> PlayerColorTeamSetting_;

	std::list<std::list<Player*>>::iterator AllPlayerIter_;
	std::list<std::list<Player*>> AllPlayer_;
	std::list<std::list<Player*>> PlayQueue_;
	std::list<Player*> DeathList_;
	Player* TargetPlayer_;

	LevelFSM LevelPhase_;


	// 카메라 업데이트
	void UpdateCamera(float4 _CameraPos);
	// 카메라의 위치
	float4 CameraPos_;
	// 카메라 이동용 이전 플레이어 위치
	float4 PrevPlayerPos_;
	// 다음 플레이어 위치
	float4 NextPlayerPos_;
	// 보간처리용 타이머
	float LerpTimer_;

	void CreateTestBullet();


	/// UI ///
	// 바람
	void SetWindUI(int _WindDir);
	// 팀 체력바
	bool UpdateTeamHpBarUI();

public:
	float4 GetWindDir()
	{
		return WindDir_;
	}

	Cursor* GetCursor()
	{
		return Mouse_;
	}
};

