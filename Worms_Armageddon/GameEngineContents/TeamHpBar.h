#pragma once
#include <GameEngine/GameEngineActor.h>
#include <vector>
#include <string>

// ���� : ���� ������ŭ HP�� ����
class GameEngineRenderer;
class TeamHpBar : public GameEngineActor
{
public:
	void InitTeamHpBar(int _TeamIndex);

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

};

