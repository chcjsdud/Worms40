#pragma once
#include "Enums.h"
#include "GameMapMaster.h"
#include "GameOptions.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineImage;
class PixelCollision : public GameEngineActor
{
public:
	bool bMissile;
	bool bGrenade;
	bool bPlayer;

public:
	void CheckPixel(CheckType _MyType, float4 _MyPos,float4 _MyScale, GameEngineImage* _ColMapImage);

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	bool CheckMissilePixelCollision();
	bool Bounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage);

	GameEngineImage* ColMapImage_;
	GameMapMaster* MapInfo_;
};

