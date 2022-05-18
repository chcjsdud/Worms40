#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
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
	GameEngineRenderer* WindGaugeRenderer_;
	GameEngineRenderer* WindR_;
	GameEngineRenderer* WindL_;
};

