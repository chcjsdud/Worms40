#include "TerrainBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

TerrainBox::TerrainBox() 
	: BoxRenderer_(nullptr)
{
}

TerrainBox::~TerrainBox() 
{
}

void TerrainBox::Start()
{
	BoxRenderer_ = CreateRenderer("LobbyMap_MapCity.bmp", (int)RenderOrder::UI);
	BoxRenderer_->SetScale({481, 166});
	BoxRenderer_->SetTransColor(RGB(0, 0, 0));
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TerrainBox::Update()
{
}

