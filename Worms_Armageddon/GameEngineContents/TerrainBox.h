#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

#include <Map>

#include "MapList.h"
#include "Enums.h"
#include "GameOptions.h"

enum class MapSelectState
{
	Wait,
	PopUpMapList,
};


// ���� :
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

	float MapListYMargin_;

	GameEngineRenderer* SelectMapBarRenderer_;			//�� ���� ��
	GameEngineRenderer* SelectMapBoxRenderer_;			//�� ���� �ڽ�
	GameEngineRenderer* SelectMapBoxArrowRenderer_;		//�� ���� ��ư
	GameEngineRenderer* SelectMapPreviewRenderer_;		//�� ������

	MapList* SelectMap_;

	GameEngineCollision* SelectMapBoxCollision_;

	MapSelectState MapSelectState_;


	std::map<std::string, MapList*> MapList_;
	std::map<std::string, MapList*>::iterator StartIter_;

	std::vector<GameEngineCollision*> MouseColCheck;

private:
	void CreateMapList(std::string _MapName);
	void CreateMapList(MapType _MapType);
	void SelectMap(MapType _MapType);
	void InitSelectMap();

	std::string MapTypeToString(MapType _MapType);
	MapType MapTypeToEnum(const std::string _MapType); //�ǵ��� �Ⱦ��°� ����.

	bool MouseLeftClick();
	bool SelectMapBoxArrow();

};

