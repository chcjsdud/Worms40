#include "TerrainBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineCustomStringSet.h>

TerrainBox::TerrainBox() 
	: 

	  MapListYMargin_(0),
	  SelectMap_(nullptr),
      SelectMapBarRenderer_(nullptr),
	  SelectMapBoxArrowRenderer_(nullptr),
	  SelectMapBoxRenderer_(nullptr),
	  SelectMapBoxCollision_(nullptr),
	  SelectMapPreviewRenderer_(nullptr),
	  MouseColCheck(),
	  MapSelectState_(MapSelectState::Wait)
{
}

TerrainBox::~TerrainBox() 
{
}

void TerrainBox::Start()
{
	SelectMapPreviewRenderer_ = CreateRenderer("LobbyMap_MapCity.bmp", static_cast<int>(RenderOrder::UI));
	SelectMapPreviewRenderer_->SetScale({481, 166});
	SelectMapPreviewRenderer_->SetPivot(SelectMapPreviewRenderer_->GetScale().Half());

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

	//TODO:: 맵 선택해야만 플레이 레벨 넘어가야함. 초기에는 맵타입이 Other로 되어있음.
	InitSelectMap();

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

		//마우스 오버
		{
			if (SelectMapBoxArrow() == true)
			{
				SelectMapBoxArrowRenderer_->SetImage("SelectMapArrow_MouseOver.bmp");
			}

			else
			{
				SelectMapBoxArrowRenderer_->SetImage("SelectMapArrow.bmp");
			}
		}

		//선택
		if (MouseLeftClick() == true && SelectMapBoxArrow() == true)
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

				//맵 선택하고 정보 넣어주기
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

	switch (_MapType)
	{
	case MapType::Birthday:

		//TODO:: BirthDay 이미지 변경
		SelectMapPreviewRenderer_ ->SetImage("MapCity.bmp");
		SelectMapPreviewRenderer_->SetScale({ 481, 166 });
		SelectMapPreviewRenderer_->SetPivot(SelectMapPreviewRenderer_->GetScale().Half());

		break;
	case MapType::Books:

		SelectMapPreviewRenderer_->SetImage("MapBooks.bmp");
		SelectMapPreviewRenderer_->SetScale({ 481, 166 });
		SelectMapPreviewRenderer_->SetPivot(SelectMapPreviewRenderer_->GetScale().Half());
		break;
	case MapType::Other:
		break;
	default:
		break;
	}
}

void TerrainBox::InitSelectMap()
{
	SelectMap_->ChangeTypeAndFont(" ", MapType::Other);
	GameOptions::PlayingOptions.SetMapType(MapType::Other);

	SelectMapPreviewRenderer_->SetImage("LobbyMap_MapCity.bmp");
	SelectMapPreviewRenderer_->SetScale({ 481, 166 });
	SelectMapPreviewRenderer_->SetPivot(SelectMapPreviewRenderer_->GetScale().Half());

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


	// 디폴트 반환
	return "";
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

	return MapType::Other;
	
}

bool TerrainBox::MouseLeftClick()
{
	return true == GameEngineInput::GetInst()->IsDown(KEY_MOUSE_LEFT);
}

bool TerrainBox::SelectMapBoxArrow()
{
	return true == SelectMapBoxCollision_->CollisionResult("Mouse", MouseColCheck);
}

