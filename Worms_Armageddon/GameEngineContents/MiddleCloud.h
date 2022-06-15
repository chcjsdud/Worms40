#pragma once
#include "Enums.h"
#include<GameEngine/GameEngineActor.h>

// Ό³Έν :
class MiddleCloud :public GameEngineActor
{
public:
	// constrcuter destructer
	MiddleCloud();
	~MiddleCloud();

	// delete Function
	MiddleCloud(const MiddleCloud& _Other) = delete;
	MiddleCloud(MiddleCloud&& _Other) noexcept = delete;
	MiddleCloud& operator=(const MiddleCloud& _Other) = delete;
	MiddleCloud& operator=(MiddleCloud&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* CloudRenderer_;
	float4 CloudDir_;
	float CloudSpeed_;
	float MySpeed_;
	int WindDir_;


public:
	inline void SetMiddleCloudDir(int  _WindDir, float _CloudSpeed)
	{
		CloudSpeed_ = MySpeed_;
		WindDir_ = _WindDir;
		CloudSpeed_ += _CloudSpeed;
	}

	inline void SetSpeed(float _Speed)
	{
		CloudSpeed_ = _Speed;
		MySpeed_ = _Speed;
	}
};

