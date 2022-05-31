#include "MapList.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

MapList::MapList()
	: 
	Font_(nullptr),
	MapListRenderer_(nullptr),
	MapListCollision_(nullptr),
	MapType_(MapType::Books)
{	
}

MapList::~MapList()
{
}

void MapList::Start()
{
	MapListRenderer_ = CreateRenderer("SelectMapListBox.bmp", static_cast<int>(RenderOrder::SelectBox));
	Font_ = GetLevel()-> CreateActor<Font>(static_cast<int>(RenderOrder::Font));
	//Font_->GameContentCreateFont("Books", float4({ -20 , 0 }));

}

void MapList::Update()
{
	//ChangeBoxImage();
}

void MapList::CreateMapList(std::string _Name)
{
	MapListCollision_ = CreateCollision(_Name, {337,8});
	Font_->SetPosition({ this->GetPosition() });
	Font_->GameContentCreateFont(_Name, float4({ -20 , 0 }));

}
void MapList::ChangeTypeAndFont(std::string _Name, MapType _MapType)
{
	MapType_ = _MapType;
	Font_->GameContentChangeFont(_Name, float4({ -20 , 0 }));
	Font_->SetPosition({ this->GetPosition() });
}
void MapList::MapListAllUpdateOff()
{
	this->Off();
	Font_->Off();
}
void MapList::MapListAllUpdateOn()
{
	this->On();
	Font_->On();
}

bool MapList::MouseLeftClick()
{
	return true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT);
}

bool MapList::MouseOver()
{
	return MapListCollision_->CollisionResult("Mouse", MouseColCheck) == true;
}

void MapList::ChangeBoxImage()
{
	if (MapListCollision_->CollisionResult("Mouse", MouseColCheck) == true)
	{
		MapListRenderer_->SetImage("SelectMapListBox_MouseOver.bmp");
	}

	else
	{
		MapListRenderer_->SetImage("SelectMapListBox.bmp");
	}
}

void MapList::SetMapType(MapType _MapType)
{
	MapType_ = _MapType;
}
