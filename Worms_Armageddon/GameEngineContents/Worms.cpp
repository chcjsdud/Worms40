#include "Worms.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LobbyLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>


Worms::Worms()
{
}

Worms::~Worms()
{
}

void Worms::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 960 });


	//레벨변경 키생성
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_PLAYLEVEL, 'P');
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_LOBBYLEVEL, 'L');


	//Image폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		GameEngineImage* TitleLogo_Actor = GameEngineImageManager::GetInst()->Find("TitleLogo_Actor.bmp");
		TitleLogo_Actor->CutCount(5, 1);

	}

	

	//Effects폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_EFFECTS);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	//Font폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_FONT);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	//Map폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_MAP);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	//Misc폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_MISC);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		GameEngineImage* cloud = GameEngineImageManager::GetInst()->Find("cloudl.bmp");
		cloud->Cut({ 160, 160 });

		GameEngineImage* wind = GameEngineImageManager::GetInst()->Find("windBar.bmp");
		wind->Cut({ 87, 13 });

	}



	//UI폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_UI);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	//WEAPONS폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_WEAPONS);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	//WORMS폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_IMAGE);
		Dir.Move(DIR_WORMS);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile(FILE_EXT_BMP);

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		{ // LEFT 용 이미지
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_AIM_LEFT);
			Image->CutCount(1, 32); 
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_IDLE_LEFT);
			Image->CutCount(1, 6);
			Image = GameEngineImageManager::GetInst()->Find(IMG_HOMING_AIM_LEFT); 
			Image->CutCount(1, 32);
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_ON_LEFT);
			Image->CutCount(1, 7);
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_OFF_LEFT);
			Image->CutCount(1, 7);
		}
		{ // RIGHT 용 이미지
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_AIM_RIGHT);
			Image->CutCount(1, 32);
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_IDLE_RIGHT);
			Image->CutCount(1, 6);
			Image = GameEngineImageManager::GetInst()->Find(IMG_HOMING_AIM_RIGHT);
			Image->CutCount(1, 32);
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_ON_RIGHT);
			Image->CutCount(1, 7);
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_OFF_RIGHT);
			Image->CutCount(1, 7);
		}
		{ // 
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_MISSILE);
			Image->Cut({ 60,60 });
		}
	}


	
	CreateLevel<TitleLevel>(LEVEL_TITLE_LEVEL);
	CreateLevel<PlayLevel>(LEVEL_PLAY_LEVEL);
	CreateLevel<LobbyLevel>(LEVEL_LOBBY_LEVEL);
	ChangeLevel(LEVEL_TITLE_LEVEL);

}

void Worms::GameLoop()
{

}
void Worms::GameEnd()
{

}