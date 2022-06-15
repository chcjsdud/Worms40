#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngineBase/GameEngineSound.h>

#include "Cursor.h"
#include "WindGauge.h"
#include "PlayShootingStar.h"

// ���� :
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

	// Lerpó���� ������ ī�޶� ��ġ
	float4 LerpStartCameraPos_;
	// ���� �ֱ��� ������ ��ġ
	float4 CurrentWeaponPos_;

	// ������ ���� ĳ���ͷ� ī�޶� �̵��Ҷ� ������ Ÿ�̸�
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

	// ���� ������
	LevelFSM LevelPhase_;
	// ���� ������
	LevelFSM PrevPhase_;


	// ī�޶� ������Ʈ
	void UpdateCamera(float4 _CameraPos);
	// ī�޶��� ��ġ
	float4 CameraPos_;
	// ī�޶� �̵��� ���� �÷��̾� ��ġ
	float4 PrevPlayerPos_;
	// ���콺�� ī�޶� ���ۿ� ���� ���콺 ��ġ
	float4 PrevCameraPos_;
	// ���콺�� ī�޶� �̵��ϴ� �÷���
	// false = ���콺�� �������� ����, true = ���콺�� ������
	bool CameraControledByWASDFlg_;
	// ���� �÷��̾� ��ġ
	float4 NextPlayerPos_;
	float4 NextDamagedPlayerPos_;
	// ����ó���� Ÿ�̸�
	float LerpTimer_;
	//��
	PlayShootingStar* PlayShootingStar_;

	// ���Ʈ����ũ�� ���ݿ� ���� ����ó��
	void PlayerDamagedCheck4AirStrike();
	void PlayerDamagedCheck4NormalWeapon();

	/// UI ///
	// �ٶ�
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

