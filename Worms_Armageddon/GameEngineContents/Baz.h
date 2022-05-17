#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class GameEngineRenderer;
class Baz :public GameEngineActor
{
public:
	// constrcuter destructer
	Baz();
	~Baz();

	// delete Function
	Baz(const Baz& _Other) = delete;
	Baz(Baz&& _Other) noexcept = delete;
	Baz& operator=(const Baz& _Other) = delete;
	Baz& operator=(Baz&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* WeaponRender_;
};

