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
	//TODO : 날라가고 , 데미지 계산 낙하데미지 폭탄데미지 모두 계산
	//날라가고 떨어지면 Idle<-로 StateChange
	//폭탄과의 거리를 계산
	//폭탄의 방향 계산 .   //// 아래에서 터지면 위로날라가고 하기위해 필요
	//폭탄데미지 + 낙하데미지 계산후 Damaged()함수에 전달 Damaged함수도 만들어야함
	//플레이어 날라가는 애니메이션 & 옆으로 미끄러지는 애니메이션도 만들어야함.

	SetMove(FlyMoveDir_ * GameEngineTime::GetDeltaTime());
	FlyMoveDir_.y += 20.0f;
}
