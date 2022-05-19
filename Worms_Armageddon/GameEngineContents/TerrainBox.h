#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TerrainBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TerrainBox();
	~TerrainBox();

	// delete Function
	TerrainBox(const TerrainBox& _Other) = delete;
	TerrainBox(TerrainBox&& _Other) noexcept = delete;
	TerrainBox& operator=(const TerrainBox& _Other) = delete;
	TerrainBox& operator=(TerrainBox&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;
private:
	GameEngineRenderer* BoxRenderer_;

};

