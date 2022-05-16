#include "PlayLevel.h"
#include "TestMap.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	TestMapActor = CreateActor<TestMap>();
}

void PlayLevel::Update()
{

}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{


}

