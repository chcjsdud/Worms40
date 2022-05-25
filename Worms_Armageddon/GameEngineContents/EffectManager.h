#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "Enums.h"

// ���� :
class GameEngineRenderer;
class EffectManager :public GameEngineActor
{
public:
	// constrcuter destructer
	EffectManager();
	~EffectManager();

	// delete Function
	EffectManager(const EffectManager& _Other) = delete;
	EffectManager(EffectManager&& _Other) noexcept = delete;
	EffectManager& operator=(const EffectManager& _Other) = delete;
	EffectManager& operator=(EffectManager&& _Other) noexcept = delete;

protected:
	//std::map<std::string, GameEngineRenderer*> AllFxObject_;

	// ���� ����Ʈ ����
	std::vector< GameEngineRenderer*> AllFxObject_;

	// ��������Ʈ�� �ߴ� ����
	int FxOrder_;

	// ����Ʈ ��ŸƮ
	FxSwitch FxSwitch_;
	bool IsStartFx_;

	// ���� ����Ʈ ����
	GameEngineRenderer* FxObject_;

	void Start() override;
	void Update() override;

private:

public:

};

