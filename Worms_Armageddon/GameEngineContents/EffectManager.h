#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "Enums.h"

// 설명 : FxObject 필터의 이펙트를 관리함
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

private:
	// 단일 이펙트 모음
	std::vector< GameEngineRenderer*> AllFxObject_;

	// 이펙트 진행상태 카운트
	int FxOffCnt_;

protected:
	// 이펙트 진행 순서
	int FxPhase_;

	// 이펙트 스타트
	bool IsStartFx_;

	bool IsRepeat_;

	void Start() override;
	void Update() override;

	// 이펙트가 끝나면 해당 이펙트를 숨기는 기능
	void FxOffUpdate();

	// 단일 이펙트를 재생하는 기능
	void FxPlay(FxPlayList _Fx);

	// 이펙트 최초생성 시간 기준으로 지정시간에 다음 페이즈로 넘겨줌
	void NextFxPhase(float _Time);

	// 해당 이펙트를 끝내는 기능
	void EffectDeath();

private: // 정의된 단일 이펙트 생성 함수
	void PlayFoom();
	void PlayCircle50();
	void PlayElipse50();
	void SupersheepSkid();
};

