#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>

// 설명 :Test용 마우스기능 
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


//마우스
private:
	POINT Mouse_;
	float4 CursorPos_;


private:
	void MouseDebugRender();

	void MouseUpdate();
};

