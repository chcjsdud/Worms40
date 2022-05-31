#pragma once
#include <GameEngine/GameEngineActor.h>
#include <string>

// ���� :
// ��ư Ŭ������ ��� ���� �� ���
// - ���콺 IN/OUT/CLICK�� üũ
// - ButtonBorderEffect ��� ����

class GameEngineCollision;
class GameEngineRenderer;
class Button : public GameEngineActor
{
protected:
	enum class MOUSE_STATE
	{
		MOUSE_IN,
		MOUSE_OUT,
		MOUSE_CLICK_LEFT,
		MOUSE_CLICK_RIGHT,
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

	inline void SetActivate(bool _Value)
	{
		IsActivated_ = _Value;
	}

	inline bool GetActivate()
	{
		return IsActivated_;
	}

	Button& ButtonInit(const std::string _ButtonName, float4 _ButtonScale, bool _IsBorderEffect = false);
protected:
	void ButtonUpdate();

	virtual void OnClickButton() {};

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

	// ��ư �׵θ� Ȱ��ȭ ���
	void ButtonBorderEffect();

private:
	MOUSE_STATE MouseState_;

	GameEngineCollision* ButtonCol_;
	GameEngineRenderer* ButtonRenderer_;
	float4 ButtonScale_;

	bool IsBorderEffect_;
	bool IsActivated_;
};

