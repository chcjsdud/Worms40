#include "ChargeBlob.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngine/GameEngineRenderer.h>

const int BlobsNum = 16;
const float BlobPadding = 4.0f;

// TODO::방향 받아서 pivot값 적용해야함
void ChargeBlob::SetChargePower(float _ChargePower, float4 _PlayerPos, float4 _ShootVec)
{
	if (false == IsSoundPlay_)
	{
		SoundPlayer_ = GameEngineSound::SoundPlayControl("throwpowerup.wav", 0);
		SoundPlayer_.Volume(SND_VOL_CHARGE);
		IsSoundPlay_ = true;
	}

	float4 ShootDir = _ShootVec;
	ShootDir.Normal2D();

	// ChargePower 0 ~ 100?
	int ActivateIndex = static_cast<int>(16 * (_ChargePower / WEAPON_MAX_SHOT_POWER));
	for (int i = 0; i < BlobsNum; i++)
	{
		if (i <= ActivateIndex)
		{
			float4 DeltaPivot = ShootDir * (BlobPadding * i) + _PlayerPos;
			Blobs_[i]->SetPivot(DeltaPivot);
			Blobs_[i]->On();
		}
		else
		{
 			Blobs_[i]->Off();
		}
	}
	
}

void ChargeBlob::DeActivate()
{
	for (auto Blob : Blobs_)
	{
		Blob->Off();
	}

	SoundPlayer_.Stop();
	IsSoundPlay_ = false;
}

ChargeBlob::ChargeBlob()
	: IsSoundPlay_(false)
{
}

ChargeBlob::~ChargeBlob() 
{
}

void ChargeBlob::Start()
{
	for (int i = 0; i < BlobsNum; i++)
	{
		GameEngineRenderer* ptr = CreateRenderer(IMG_FX_BLOB, (int)RenderOrder::UI);
		ptr->SetIndex(i);
		ptr->SetPivot({ i * 4.0f, 0 });
		Blobs_.push_back(ptr);
	}	

	DeActivate();
}

