#include "Worms.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>


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
	//GameEngineInput::GetInst()->CreateKey("ChangePlayLevel", '0');



	//Image폴더내 파일 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParent("Worms_Armageddon");
		Dir.Move("Resources");
		Dir.Move("Image");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}



	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	ChangeLevel("TitleLevel");


}

void Worms::GameLoop()
{

}
void Worms::GameEnd()
{

}