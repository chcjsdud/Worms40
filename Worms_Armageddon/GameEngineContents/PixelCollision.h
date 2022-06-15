#pragma once
#include "Enums.h"
#include "GameMapMaster.h"
#include "GameOptions.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>

// 설명 :
class GameEngineImage;
class PixelCollision : public GameEngineActor
{
public:
	PixelCollision();
	~PixelCollision();
	bool bMissile;
	bool bGrenade;
	bool bPlayer;

public:
	float4 Bounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _BulletDir);
	float4 PlayerBounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _MoveDir, float _JumpSpeed);
	float4 PlayerFlyBounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _MoveDir, float _FlySpeed);
	float4 PlayerSlideBounce(float4 _ActorPos, float4 _ActorScale, GameEngineImage* _ColMapImage, float4 _MoveDir, float _FlySpeed);
	inline bool GetBounceFlg() const
	{
		return BounceFlg_;
	}

	inline void SetBounceFlgFalse()
	{
		BounceFlg_ = false;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

	GameEngineImage* ColMapImage_;
	GameMapMaster* MapInfo_;

	// 7  0  1
	// 6     2
	// 5  4  3
	// 꼭짓점 충돌에 대한 플래그
	bool ColorFlag_[8];

	// 충돌 자체에 대한 플래그(감속용)
	bool BounceFlg_;

	float4 MoveDir_;
};

