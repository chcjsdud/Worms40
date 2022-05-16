#pragma once
#include <GameEngine/GameEngineActor.h>


// ���� :	PlayLevel���� �׽�Ʈ������ �� BackGorundActor Ŭ����
class TestMap	:public GameEngineActor
{
public:
	// constrcuter destructer
	TestMap();
	~TestMap();

	// delete Function
	TestMap(const TestMap& _Other) = delete;
	TestMap(TestMap&& _Other) noexcept = delete;
	TestMap& operator=(const TestMap& _Other) = delete;
	TestMap& operator=(TestMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* BackGround;
	GameEngineRenderer* ColImage;

private:
	bool ChangeMode;


private:
	void ChangePixelMode();
};

