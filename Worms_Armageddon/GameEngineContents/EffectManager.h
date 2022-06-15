#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include "Enums.h"

// ���� : FxObject ������ ����Ʈ�� ������
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
	// ���� ����Ʈ ����
	std::vector< GameEngineRenderer*> AllFxObject_;

	// ����Ʈ ������� ī��Ʈ
	int FxOffCnt_;

protected:
	// ����Ʈ ���� ����
	int FxPhase_;

	// ����Ʈ ��ŸƮ
	bool IsStartFx_;

	bool IsRepeat_;

	void Start() override;
	void Update() override;

	// ����Ʈ�� ������ �ش� ����Ʈ�� ����� ���
	void FxOffUpdate();

	// ���� ����Ʈ�� ����ϴ� ���
	void FxPlay(FxPlayList _Fx);

	// ����Ʈ ���ʻ��� �ð� �������� �����ð��� ���� ������� �Ѱ���
	void NextFxPhase(float _Time);

	// �ش� ����Ʈ�� ������ ���
	void EffectDeath();

private: // ���ǵ� ���� ����Ʈ ���� �Լ�
	void PlayFoom();
	void PlayCircle50();
	void PlayElipse50();
	void SupersheepSkid();
};

