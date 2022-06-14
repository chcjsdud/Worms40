#include "GameOptions.h"

GameOptions GameOptions::PlayingOptions;

GameOptions::GameOptions()
	: MapType_(MapType::Other)
	, TurnTime_(0)
	, WormzHp_ (100)
{
}

GameOptions::~GameOptions()
{
}
