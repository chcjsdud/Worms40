#include "PlayLevel.h"
#include "PlayLevelTestMap.h"
#include "Player.h"
#include "WeaponMaster.h"
#include "Cursor.h"
#include "GameEngineBase/GameEngineRandom.h"
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
	//���ȭ�� ����
	PlayLevelTestMap_ = CreateActor<PlayLevelTestMap>();
	//���콺
	Mouse_ = CreateActor<Cursor>((int)ActorGroup::UI);
	//�ٶ� ������
	WindGaugeActor_ = CreateActor<WindGauge>((int)ActorGroup::UI);
	WindGaugeActor_->SetPosition({ 1000,600 });
	//����
	LargeCloudActor_ = CreateActor<LargeCloud>();
	LargeCloudActor_->SetPosition({ 200,200 });
	


	WeaponTset_ = CreateActor<WeaponMaster>();
	// �׽�Ʈ�� �ڵ�

	// TODO::����
	Player_ = CreateActor<Player>();

	if (false == GameEngineInput::GetInst()->IsKey("TestClick"))
	{
		GameEngineInput::GetInst()->CreateKey("TestClick", VK_LBUTTON);
	}

	WindSpeed_ = 45.0f;
}

void PlayLevel::Update()
{

	//�ӽù���
	//���콺 Ŭ���Ҷ����� �ٶ����� ����
	if (GameEngineInput::GetInst()->IsDown("TestClick"))
	{
		GameEngineRandom Ran;
		int WinInt = Ran.RandomInt(0, 1);

		SetWindUI(WinInt);
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

void PlayLevel::SetWindUI(int _WindDir)
{
	//�ٶ� ������ �����̶��
	if (_WindDir == (int)WindType::Left)
	{
		GameEngineRandom Ran;

		//�ٶ� ���⸦ �����ϰ� �޴´�
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		//�ٶ�������UI�� �ٶ������ �ӵ��� �Ѱ��ش�
		WindGaugeActor_->SetWind(WindType::Left,WindSpeed_);
		//����Actor���� �Ѱ��ش�
		LargeCloudActor_->SetCloudDir(_WindDir, WindSpeed_);
	}
	else
	{
		GameEngineRandom Ran;
		WindSpeed_ = Ran.RandomFloat(0, 100.0f);
		WindDir_ = float4::RIGHT * WindSpeed_;
		WindGaugeActor_->SetWind(WindType::Right, WindSpeed_);
		LargeCloudActor_->SetCloudDir(_WindDir,WindSpeed_);
	}
}

