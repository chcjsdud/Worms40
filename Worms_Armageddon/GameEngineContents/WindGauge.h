#pragma once
#include "Enums.h"
#include <GameEngine/GameEngineActor.h>

// 설명 :
class WindGauge	:public GameEngineActor
{
public:
	// constrcuter destructer
	WindGauge();
	~WindGauge();

	// delete Function
	WindGauge(const WindGauge& _Other) = delete;
	WindGauge(WindGauge&& _Other) noexcept = delete;
	WindGauge& operator=(const WindGauge& _Other) = delete;
	WindGauge& operator=(WindGauge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	//윈드게이지 UI바 이미지
	GameEngineRenderer* WindGaugeRenderer_;
	//방향 UI이미지
	GameEngineRenderer* WindLeftRenderer_;
	GameEngineRenderer* WindRightRenderer_;

	//wind 방향UI 가리는 이미지
	GameEngineRenderer* WindLeftHiderRenderer_;
	GameEngineRenderer* WindRightHiderRenderer_;

	float MaxWindFigure_;
	float WindFigure_;
	float HideWindFigure_;
	float MyWindFigure_;

	float WindRightHider_x;
	float WindLeftHider_x;
	WindType WindDir_;

	bool IsEnd;

public:
	inline void SetWind(WindType _WindDir,float _WindFigure)
	{
		WindDir_ = _WindDir;
		WindFigure_ = _WindFigure;
	}

};

