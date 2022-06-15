#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class SmallCloud	:	public GameEngineActor
{
public:
	// constrcuter destructer
	SmallCloud();
	~SmallCloud();

	// delete Function
	SmallCloud(const SmallCloud& _Other) = delete;
	SmallCloud(SmallCloud&& _Other) noexcept = delete;
	SmallCloud& operator=(const SmallCloud& _Other) = delete;
	SmallCloud& operator=(SmallCloud&& _Other) noexcept = delete;

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
	inline void SetSmallCloudDir(int  _WindDir, float _CloudSpeed)
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

