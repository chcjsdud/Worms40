#include "Crosshair.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>

Crosshair::Crosshair()
	: Renderer_(nullptr)
	, Distance_(80.0f)
{
}

Crosshair::~Crosshair() 
{
}

void Crosshair::UpdateCrosshairPos(float4 _PlayerPos, float4 _ShootVec, bool _Activate)
{
	// 활성화 여부
	if (false == _Activate)
	{
		Renderer_->Off();
		return;
	}
	Renderer_->On();

	float4 ShootDir = _ShootVec;
	ShootDir.Normal2D();

	float4 CrossHairPos = ShootDir * Distance_ + _PlayerPos;
	SetPosition(CrossHairPos);
	
	float Degree = float4::VectorXYtoDegree(_PlayerPos, CrossHairPos);
	Renderer_->SetRotationZ(Degree);
}

void Crosshair::Start()
{
	Renderer_ = CreateRenderer(IMG_CRSHIR_RED, (int)RenderOrder::UI);
	Renderer_->SetRotationFilter(IMG_CRSHIR_FILTER);
}

