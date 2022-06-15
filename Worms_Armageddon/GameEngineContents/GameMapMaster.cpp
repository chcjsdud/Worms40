#include "GameMapMaster.h"

GameMapMaster::GameMapMaster()
	: BackGround_(nullptr)
	, Ground_(nullptr)
	, ColMap_(nullptr)
	, ColMapRenderer_(nullptr)
	, WaterActor_(nullptr)

{
	// √ ±‚»≠
	for (int i = 0; i < PLAYER_MAX_NUMBER; i++)
	{
		ResponPosition_[i] = float4::ZERO;
		PositionFlg_[i] = false;
	}
}

GameMapMaster::~GameMapMaster() 
{
}

