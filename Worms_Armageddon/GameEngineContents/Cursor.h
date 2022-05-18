#pragma once
#include <Windows.h>
#include <GameEngine/GameEngineActor.h>

// 설명 :Test용 마우스기능 
class Cursor : public GameEngineActor
{
public:
	// constrcuter destructer
	Cursor();
	~Cursor();

	// delete Function
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void CursorDebugRender();
	void CursorUpdate();

private:
	class GameEngineRenderer* Renderer_;

	POINT MousePos_;
	float4 CursorPos_;


};

