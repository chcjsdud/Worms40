#include "CreditLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

CreditLevel::CreditLevel() 
	: Credit_(nullptr)
	, FadeIn_(nullptr)
{
}

CreditLevel::~CreditLevel() 
{
}

void CreditLevel::Loading()
{
	Credit_ = CreateActor<Credit>();
	FadeIn_ = CreateActor<FadeIn>();
}

void CreditLevel::Update()
{

}

