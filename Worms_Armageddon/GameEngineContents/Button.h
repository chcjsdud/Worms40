#pragma once
#include <GameEngine/GameEngineActor.h>
#include <string>

// Ό³Έν :
class Button : public GameEngineActor
{
protected:
	enum class MOUSE_STATE
	{
		MOUSE_IN,
		MOUSE_OUT,
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
	void ButtonInit(std::string _Name, float4 _Size);
	void ButtonUpdate();

	virtual void OnClickButton() = 0;

	MOUSE_STATE GetMouseState()
	{
		return State_;
	}

protected:
	std::string ButtonName_;

private:
	void ChangeState(MOUSE_STATE _ButtonName);
	void UpdateState();

private:
	MOUSE_STATE State_;

	class GameEngineCollision* ButtonCol_;
};

