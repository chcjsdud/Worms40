#include "Player.h"
void Player::UncontrolledStart()
{

}

void Player::UncontrolFlyAwayStart()
{
	FlyMoveDir_ = float4{ 300,-800 };
}


void Player::UncontrolledUpdate()
{

}

void Player::UncontrolFlyAwayUpdate()
{
	//TODO : ���󰡰� , ������ ��� ���ϵ����� ��ź������ ��� ���
	//���󰡰� �������� Idle<-�� StateChange
	//��ź���� �Ÿ��� ���
	//��ź�� ���� ��� .   //// �Ʒ����� ������ ���γ��󰡰� �ϱ����� �ʿ�
	//��ź������ + ���ϵ����� ����� Damaged()�Լ��� ���� Damaged�Լ��� ��������
	//�÷��̾� ���󰡴� �ִϸ��̼� & ������ �̲������� �ִϸ��̼ǵ� ��������.

	SetMove(FlyMoveDir_ * GameEngineTime::GetDeltaTime());
	FlyMoveDir_.y += 20.0f;
}
