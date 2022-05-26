#include "TeamColorButton.h"

TeamColorButton::TeamColorButton() 
{
}

TeamColorButton::~TeamColorButton() 
{
}

void TeamColorButton::Start()
{
	Button::ButtonInit("RedTeam", { 20, 20 }, true);
}

void TeamColorButton::Update()
{
	Button::ButtonUpdate();

}

void TeamColorButton::OnClickButton()
{
}
