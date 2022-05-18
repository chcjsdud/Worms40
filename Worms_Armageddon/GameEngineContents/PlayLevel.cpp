#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "PlayLevelTestMouse.h"
#include "Player.h"
#include "WeaponMaster.h"
#include <GameEngineBase/GameEngineInput.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{

}

void PlayLevel::Loading()
{
	// �׽�Ʈ�� �ڵ�
	PlayLevelTestMap_ = CreateActor<PlayLevelTestMap>();
	
	PlayLevelTestMouse_ = CreateActor<PlayLevelTestMouse>();


	LargeCloudActor_ = CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200,200 });
	BazTset_ = CreateActor<Baz>();
	WeaponTset_ = CreateActor<WeaponMaster>();
	// �׽�Ʈ�� �ڵ�

	// TODO::����
	//Player_ = CreateActor<Player>();

	if (false == GameEngineInput::GetInst()->IsKey("TestClick"))
	{
		GameEngineInput::GetInst()->CreateKey("TestClick", VK_LBUTTON);
	}

}

void PlayLevel::Update()
{

	if (GameEngineInput::GetInst()->IsDown("TestClick"))
	{
		int a = 0;
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{


}

void PlayLevel::CreateTestBullet()
{

}

