#include "WindGauge.h"
#include "GameEngine/GameEngineRenderer.h"

WindGauge::WindGauge() 
{
}

WindGauge::~WindGauge() 
{
}

void WindGauge::Start()
{
	WindGaugeRenderer_ = CreateRenderer("WindGauge.bmp");
	WindR_ = CreateRenderer("windr.bmp", (int)RenderPivot::LEFT);
	WindL_ = CreateRenderer("windl.bmp", (int)RenderPivot::RIGHT);

}

void WindGauge::Update()
{

}

void WindGauge::Render()
{

}
