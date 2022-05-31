#pragma once
#include "GameMapMaster.h"

// Ό³Έν :
class GameEngineImage;
class MapBooks : public GameMapMaster
{
public:
	// constrcuter destructer
	MapBooks();
	~MapBooks();

	// delete Function
	MapBooks(const MapBooks& _Other) = delete;
	MapBooks(MapBooks&& _Other) noexcept = delete;
	MapBooks& operator=(const MapBooks& _Other) = delete;
	MapBooks& operator=(MapBooks&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;


private:
	bool ShowColMap_;
};

