#include "TerrainBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

TerrainBox::TerrainBox() 
	: 

	  MapListYMargin_(0),
	  SelectMap_(nullptr),
	  BoxRenderer_(nullptr),
      SelectMapBarRenderer_(nullptr),
	  SelectMapBoxArrowRenderer_(nullptr),
	  SelectMapBoxRenderer_(nullptr),
	  SelectMapBoxCollision_(nullptr),
	  MouseColCheck(),
	  MapSelectState_(MapSelectState::Wait)
{
}

TerrainBox::~TerrainBox() 
{
}

void TerrainBox::Start()
{
	BoxRenderer_ = CreateRenderer("LobbyMap_MapCity.bmp", static_cast<int>(RenderOrder::UI));
	BoxRenderer_->SetScale({481, 166});
	BoxRenderer_->SetTransColor(RGB(0, 0, 0));
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());

	SelectMapBarRenderer_ = CreateRenderer("SelectMap.bmp", static_cast<int>(RenderOrder::SelectBox));
	SelectMapBarRenderer_->SetPivot({300, 210});

	SelectMapBoxRenderer_ = CreateRenderer("SelectBox.bmp", static_cast<int>(RenderOrder::SelectBox));
	SelectMapBoxRenderer_->SetPivot({ 300, 330 });
	SelectMapBoxRenderer_->Off();

	SelectMapBoxArrowRenderer_ = CreateRenderer("SelectBox.bmp", static_cast<int>(RenderOrder::SelectBox));
	SelectMapBoxArrowRenderer_->SetPivot({ 300, 210 });

	SelectMapBoxCollision_ = CreateCollision("SelectMapbox", {30, 28});
	SelectMapBoxCollision_->SetPivot({ 465, 210 });

	CreateMapList(MapType::Books);
	CreateMapList(MapType::Birthday);

	SelectMap_ = GetLevel()->CreateActor<MapList>();
	SelectMap_->SetPosition({ 300 + 776, 255 - 24 });
	SelectMap_->GetRenderer()->Off();
	//SelectMap_->CreateMapList("Books");
	SelectMap(MapType::Books);


	std::map<std::string, MapList*>::iterator Start = MapList_.begin();
	std::map<std::string, MapList*>::iterator End = MapList_.end();

	for (; Start != End; ++Start)
	{
		Start->second->MapListAllUpdateOff();
	}

}

void TerrainBox::Update()
{

	switch (MapSelectState_)
	{
	case MapSelectState::Wait:

		if (MouseOver() == true)
		{
			SelectMapBoxArrowRenderer_->SetImage("SelectMapArrow_MouseOver.bmp");
		}

		else
		{
			SelectMapBoxArrowRenderer_->SetImage("SelectMapArrow.bmp");
		}

		if (MouseLeftClick() == true && MouseOver() == true)
		{
			StartIter_ = MapList_.begin();

			for (; StartIter_ != MapList_.end(); ++StartIter_)
			{
				StartIter_->second->MapListAllUpdateOn();
			}

			SelectMapBoxRenderer_->On();
			MapSelectState_ = MapSelectState::PopUpMapList;
		}

		break;
	case MapSelectState::PopUpMapList:

		StartIter_ = MapList_.begin();

		for (; StartIter_ != MapList_.end(); ++StartIter_)
		{
			StartIter_->second->ChangeBoxImage();

			if (StartIter_->second->MouseLeftClick() == true && StartIter_->second->MouseOver() == true)
			{
				MapType MapType = StartIter_->second->GetMapType();
				SelectMap(MapType);

				StartIter_ = MapList_.begin();

				for (; StartIter_ != MapList_.end(); ++StartIter_)
				{
					StartIter_->second->MapListAllUpdateOff();
				}

				SelectMapBoxRenderer_->Off();
				MapSelectState_ = MapSelectState::Wait;
				break;
			}
		}

		break;
	default:
		break;
	}
}

void TerrainBox::CreateMapList(std::string _MapName)
{

	MapType MapType = MapTypeToEnum(_MapName);
	MapList_.insert(std::make_pair(_MapName, GetLevel()->CreateActor<MapList>()));

	std::map<std::string, MapList*>::iterator FindMapList = MapList_.find(_MapName);
	FindMapList->second->SetPosition({ 300 + 776, 255 + MapListYMargin_});
	FindMapList->second->CreateMapList(_MapName);
	FindMapList->second->SetMapType(MapType);


	MapListYMargin_ += 18;

}

void TerrainBox::CreateMapList(MapType _MapType)
{

	std::string MapName = MapTypeToString(_MapType);

	MapList_.insert(std::make_pair(MapName, GetLevel()->CreateActor<MapList>()));

	std::map<std::string, MapList*>::iterator FindMapList = MapList_.find(MapName);
	FindMapList->second->SetPosition({ 300 + 776, 255 + MapListYMargin_ });
	FindMapList->second->CreateMapList(MapName);
	FindMapList->second->SetMapType(_MapType);

	MapListYMargin_ += 18;
}

void TerrainBox::SelectMap(MapType _MapType)
{
	std::string MapName = MapTypeToString(_MapType);
	SelectMap_->ChangeTypeAndFont(MapName, _MapType);
	GameOptions::PlayingOptions.SetMapType(_MapType);
}

std::string TerrainBox::MapTypeToString(MapType _MapType)
{
	switch (_MapType)
	{
	case MapType::Birthday:

		return "Birthday";

		break;
	case MapType::Books:

		return "Books";

		break;
	default:
		break;
	}
}

MapType TerrainBox::MapTypeToEnum(const std::string _MapType)
{
	if (_MapType == "Books")
	{
		return MapType::Books;
	}

	else if (_MapType == "Birthday")
	{
		return MapType::Birthday;
	}

	else

	{
		return MapType::Other;
	}

}

bool TerrainBox::MouseLeftClick()
{
	return true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT);
}

bool TerrainBox::MouseOver()
{
	return true == SelectMapBoxCollision_->CollisionResult("Mouse", MouseColCheck);
}

