#include "Credit.h"
#include "GameEngineBase//GameEngineWindow.h"

Credit::Credit() 
	:
	CreditRenderer_(nullptr)
{
}

Credit::~Credit() 
{
}

void Credit::Start()
{
	CreditRenderer_ = CreateRenderer("Worms_EndingBackDrop��.bmp");
	this->SetPosition({ GameEngineWindow::GetInst().GetScale().Half()});
}

