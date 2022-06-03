#include "AirStrike.h"
#include "Cursor.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

AirStrike::AirStrike() 
{
}

AirStrike::~AirStrike() 
{
}

void AirStrike::Start()
{
	
}

void AirStrike::Update()
{

}

bool AirStrike::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}
	
	AirStart(float4::LEFT); // ���ݱ� ���
	// ���ݱⰡ ��θ� �� �������� ���� �� �Ѿ

	Bombing(WeaponState::AirStrike);


	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}