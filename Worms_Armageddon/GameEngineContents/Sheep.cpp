#include "Sheep.h"
#include "SuperSheep.h"
#include "PixelCollision.h"
#include "TimerBox.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

Sheep::Sheep() 
	: TimerBox_(nullptr)
{
}

Sheep::~Sheep() 
{
}

void Sheep::Start()
{
	IsBounce_ = true;
	PixelCol_ = GetLevel()->CreateActor<PixelCollision>();
	WeaponRender_ = CreateRenderer((int)RenderOrder::Weapon);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_LEFT, ANIM_NAME_SHEEP_LEFT, 0, 7, 0.04f);
	WeaponRender_->CreateAnimation(IMG_SHEEP_BULLET_RIGHT, ANIM_NAME_SHEEP_RIGHT, 0, 7, 0.04f);
	WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_LEFT);
}

void Sheep::Update()
{

}

bool Sheep::WeaponUpdate()
{
	// �׽�Ʈ
	if (true == GameEngineInput::GetInst()->IsDown(KEY_MOVE_JUMP))
	{
		// ���Ⱑ �����ϰ� 
		// ���� �� - > �÷��̾��� State�� ����, ������
		return false;
	}

	if (7.0f < GetAccTime()) // 20�� �� ����
	{
		Explosion();
		TimerBox_->DeleteGrenadeBox();
		return false;
	}

	//Ÿ�̸� �ڽ� ��ġ
	if (TimerBox_ != nullptr)
	{
		TimerBox_->TimerBoxSetPosition({ this->GetPosition().x, this->GetPosition().y - 50.f });
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_FIRE)) // ����
	{
		Explosion();
		return false;
	}

	if (1 == ShotDir_.x) // ���� �ٶ󺸴� ������ ������
	{
		WeaponRender_->ChangeAnimation(ANIM_NAME_SHEEP_RIGHT);
	}

	ThrowStart(0); // ����ü�� ������
	AnimalMove(); // ���� �����̴ٰ�

	if (false == IsUpdate()) // ��� ü���� ���� �� false ���ϵǵ��� ���� ����
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Sheep::CreateTimerBox(TeamColor _Color)
{
	TimerBox_ = GetLevel()->CreateActor<TimerBox>();
	TimerBox_->CreateTimerBox(static_cast<FONT_COLOR>(_Color), 20);
}
