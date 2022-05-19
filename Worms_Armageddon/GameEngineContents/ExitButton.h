#pragma once

// Ό³Έν :
class ExitButton
{
public:
	// constrcuter destructer
	ExitButton();
	~ExitButton();

	// delete Function
	ExitButton(const ExitButton& _Other) = delete;
	ExitButton(ExitButton&& _Other) noexcept = delete;
	ExitButton& operator=(const ExitButton& _Other) = delete;
	ExitButton& operator=(ExitButton&& _Other) noexcept = delete;

protected:

private:

};

