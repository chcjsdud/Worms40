#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "Enums.h"

// 설명 :
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

	// 단일 이펙트 모음
	std::list< GameEngineRenderer*> AllFxObject_;
	int FxOffCnt_;

	// 단일이펙트가 뜨는 순서
	int FxOrder_;

	// 이펙트 스타트
	bool IsStartFx_;

	// 단일 이펙트 랜더
	GameEngineRenderer* FxObject_;

	void Start() override;
	void Update() override;

	void FxOff();

private:
	

public:


	//void PlayFx(FxPlayList _Fx);
};

