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
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_PLAYLEVEL, VK_RETURN);
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_LOBBYLEVEL, VK_SPACE);



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

		{
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("bazTest.bmp");
			Image->CutCount(1, 32);
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