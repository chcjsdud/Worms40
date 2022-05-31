#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

#include "Font.h"
#include "Enums.h"

// Ό³Έν :
class GameEngineRenderer;
class MapList : public GameEngineActor
{
public:
	// constrcuter destructer
	MapList();
	~MapList();

	// delete Function
	MapList(const MapList& _Other) = delete;
	MapList(MapList&& _Other) noexcept = delete;
	MapList& operator=(const MapList& _Other) = delete;
	MapList& operator=(MapList&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	GameEngineRenderer* MapListRenderer_;
	GameEngineCollision* MapListCollision_;

	Font* Font_;

	MapType MapType_;

	std::vector<GameEngineCollision*> MouseColCheck;

public:
	void CreateMapList(std::string _Name);
	void ChangeTypeAndFont(std::string _Name, MapType _MapType);
	void MapListAllUpdateOff();
	void MapListAllUpdateOn();
	void ChangeBoxImage();

	void SetMapType(MapType _MapType);

	bool MouseLeftClick();
	bool MouseOver();


	MapType GetMapType() const
	{
		return MapType_;
	}
	 
	GameEngineRenderer* GetRenderer() const
	{
		return MapListRenderer_;
	}

};

