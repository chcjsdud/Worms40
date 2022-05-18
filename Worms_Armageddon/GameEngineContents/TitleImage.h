#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class TitleImage : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleImage();
	~TitleImage();

	// delete Function
	TitleImage(const TitleImage& _Other) = delete;
	TitleImage(TitleImage&& _Other) noexcept = delete;
	TitleImage& operator=(const TitleImage& _Other) = delete;
	TitleImage& operator=(TitleImage&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* TitleImageRenderer_;


public:
	GameEngineRenderer* GetRenderer()
	{
		return TitleImageRenderer_;
	}
};

