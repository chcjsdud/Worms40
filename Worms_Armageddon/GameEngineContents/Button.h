#pragma once
#include <GameEngine/GameEngineActor.h>
#include <string>

// 설명 :
class GameEngineCollision;
class GameEngineRenderer;
class Button : public GameEngineActor
{
protected:
	enum class MOUSE_STATE
	{
		MOUSE_IN,
		MOUSE_OUT,
		MOUSE_CLICK,
	};

public:
	// constrcuter destructer
	Button();
	virtual ~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

protected:
	void ButtonInit(const std::string _ButtonName, const std::string _ImageName);
	void ButtonUpdate();

	virtual void OnClickButton() = 0;

	MOUSE_STATE GetMouseState()
	{
		return MouseState_;
	}

	GameEngineRenderer* GetRenderer()
	{
		return ButtonRenderer_;
	}

	GameEngineCollision* GetCollision()
	{
		return ButtonCol_;
	}

protected:
	std::string ButtonName_;

private:
	void ChangeState(MOUSE_STATE _MouseState);
	void UpdateState();

	void MouseInUpdate();
	void MouseInOutCheck();

	// 버튼 테두리 활성화 기능
	void ButtonBorderEffect();

private:
	MOUSE_STATE MouseState_;

	GameEngineCollision* ButtonCol_;
	GameEngineRenderer* ButtonRenderer_;
};

