#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>

// ���� :Test�� ���콺��� 
class PlayLevelTestMouse :public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevelTestMouse();
	~PlayLevelTestMouse();

	// delete Function
	PlayLevelTestMouse(const PlayLevelTestMouse& _Other) = delete;
	PlayLevelTestMouse(PlayLevelTestMouse&& _Other) noexcept = delete;
	PlayLevelTestMouse& operator=(const PlayLevelTestMouse& _Other) = delete;
	PlayLevelTestMouse& operator=(PlayLevelTestMouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* BulletRenderer_;


//���콺
private:
	POINT Mouse_;
	float4 CursorPos_;


private:
	void MouseDebugRender();

	void MouseUpdate();
};

