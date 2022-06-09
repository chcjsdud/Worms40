#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <string>
#include "UIMaster.h"

// 설명 : 팀의 개수만큼 HP바 생성
class GameEngineRenderer;
class TeamHpBar : public UIMaster
{
public:
	void InitTeamHpBar(int _TeamIndex, int _MemberNum);

	void DecreaseInit(int _Damage);
	bool Decrease();

	inline float GetCurrentHp()
	{
		return CurrentHp_;
	}

public:
	// constrcuter destructer
	TeamHpBar();
	~TeamHpBar();

	// delete Function
	TeamHpBar(const TeamHpBar& _Other) = delete;
	TeamHpBar(TeamHpBar&& _Other) noexcept = delete;
	TeamHpBar& operator=(const TeamHpBar& _Other) = delete;
	TeamHpBar& operator=(TeamHpBar&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:

	GameEngineRenderer* TeamNameRenderer_;
	GameEngineRenderer* TeamFlagRenderer_;
	GameEngineRenderer* TeamHpBarRenderer_;

	float TotalHp_;
	float CurrentHp_;
	float TargetHp_;
	float BarWidth_;
	float4 BarPivot_;
};

