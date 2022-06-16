#include "Worms.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "LobbyLevel.h"
#include "CreditLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>


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
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_LOBBYLEVEL, '1');
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_PLAYLEVEL, VK_SHIFT);
	GameEngineInput::GetInst()->CreateKey(KEY_CHANGE_CREDITLEVEL, VK_CONTROL);

	//마우스 클릭 키생성
	GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_LEFT, VK_LBUTTON);
	GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_MID, VK_MBUTTON);
	GameEngineInput::GetInst()->CreateKey(KEY_MOUSE_RIGHT, VK_RBUTTON);

	GameEngineInput::GetInst()->CreateKey(KEY_CAMERAMOVE_UP, 'W');
	GameEngineInput::GetInst()->CreateKey(KEY_CAMERAMOVE_DOWN, 'S');
	GameEngineInput::GetInst()->CreateKey(KEY_CAMERAMOVE_LEFT, 'A');
	GameEngineInput::GetInst()->CreateKey(KEY_CAMERAMOVE_RIGHT, 'D');


	GameEngineInput::GetInst()->CreateKey(DEBUG_KEY, 'P');


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

		{
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_FX_EXFOOM);
			Image->Cut({ 100,100 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_FX_CIRCLE50);
			Image->Cut({ 100,100 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_FX_ELIPSE50);
			Image->Cut({ 150,150 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_FX_BLOB);
			Image->Cut({ 64, 64 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_FX_SKIDMARK_SPSHEEP);
			Image->Cut({ 60, 60 });
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

		GameEngineImage* Font = GameEngineImageManager::GetInst()->Find("FontEdit.bmp");
		Font->Cut({ 16, 16 });

		GameEngineImage* HPnumber = GameEngineImageManager::GetInst()->Find("HPnumber.bmp");
		HPnumber->Cut({ 12, 12 });

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

		GameEngineImage* Water = GameEngineImageManager::GetInst()->Find("Water_sprite.bmp");
		Water->Cut({ 2560, 100 });


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

		GameEngineImage* cloudl = GameEngineImageManager::GetInst()->Find("cloudl.bmp");
		cloudl->Cut({ 160, 160 });

		GameEngineImage* cloudm = GameEngineImageManager::GetInst()->Find("cloudm.bmp");
		cloudm->Cut({ 128, 128 });

		GameEngineImage* clouds = GameEngineImageManager::GetInst()->Find("clouds.bmp");
		clouds->Cut({ 60, 60 });

		GameEngineImage* wind = GameEngineImageManager::GetInst()->Find("windBar.bmp");
		wind->Cut({ 87, 13 });

		GameEngineImage* ScatterLeaf = GameEngineImageManager::GetInst()->Find("ScatterLeaf.bmp");
		ScatterLeaf->Cut({ 32, 32 });

		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("markerp.bmp");
		Image->Cut({ 60,60 });
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

		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("stars.bmp");
		Image->Cut({ 24, 24 });

		GameEngineImage* ArrowBlue = GameEngineImageManager::GetInst()->Find("ArrowBlue.bmp");
		ArrowBlue->Cut({ 60, 60 });

		GameEngineImage* arrowGreen = GameEngineImageManager::GetInst()->Find("arrowGreen.bmp");
		arrowGreen->Cut({ 60, 60 });

		GameEngineImage* arrowMint = GameEngineImageManager::GetInst()->Find("arrowMint.bmp");
		arrowMint->Cut({ 60, 60 });

		GameEngineImage* arrowPink = GameEngineImageManager::GetInst()->Find("arrowPink.bmp");
		arrowPink->Cut({ 60, 60 });

		GameEngineImage* ArrowRed = GameEngineImageManager::GetInst()->Find("ArrowRed.bmp");
		ArrowRed->Cut({ 60, 60 });

		GameEngineImage* ArrowYellow = GameEngineImageManager::GetInst()->Find("ArrowYellow.bmp");
		ArrowYellow->Cut({ 60, 60 });
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
		{
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_BULLET_LEFT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_BULLET_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_SUPERSHEEP_FLY);
			Image->Cut({ 60, 60 });
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
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_IDLE_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_JUMPRDY_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYLINK_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYDOWN_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_BACKFLIP_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_WALK_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYLINK_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_ON_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_OFF_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_GRN_OFF_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_GRN_ON_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_AIRSTRIKE_OFF_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_AIRSTRIKE_ON_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_ON_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_OFF_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_FLY_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_DIE_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_DIE_RIGHT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_WIN_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_WIN_RIGHT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_SLIDE_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_SLIDE_RIGHT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_SLIDE_UP_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_SLIDE_UP_RIGHT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_BREATH_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_BREATH_RIGHT);
		Image->Cut({ 60, 60 });


		//무기
		Image = GameEngineImageManager::GetInst()->Find(IMG_HOMING_AIM_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_ON_LEFT);
		Image->Cut({ 60, 60 });
		Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_OFF_LEFT);
		Image->Cut({ 60, 60 });
		}
		{ // RIGHT 용 이미지
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_AIM_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_IDLE_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_JUMPRDY_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYLINK_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYDOWN_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_BACKFLIP_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_WALK_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FLYLINK_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_ON_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_BAZ_OFF_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_GRN_OFF_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_GRN_ON_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_AIRSTRIKE_OFF_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_AIRSTRIKE_ON_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_ON_RIGHT);
			Image->Cut({ 60, 60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_SHEEP_OFF_RIGHT);
			Image->Cut({ 60, 60 });


			//무기
			Image = GameEngineImageManager::GetInst()->Find(IMG_HOMING_AIM_RIGHT);
			Image->Cut({ 60, 60 });


		}
		{
			GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FALL_LEFT);
			Image->Cut({ 60,60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_FALL_RIGHT);
			Image->Cut({ 60,60 });
			Image = GameEngineImageManager::GetInst()->Find(IMG_PLAYER_GRAVE);
			Image->Cut({ 60,60 });
		}
	}

	// 사운드 파일 로딩
	{
		GameEngineDirectory Dir;
		Dir.MoveParent(DIR_WORMS_PARENTS);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_SOUND);

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}
	}
	
	CreateLevel<TitleLevel>(LEVEL_TITLE_LEVEL);
	CreateLevel<PlayLevel>(LEVEL_PLAY_LEVEL);
	CreateLevel<LobbyLevel>(LEVEL_LOBBY_LEVEL);
	CreateLevel<CreditLevel>(LEVEL_CREDIT_LEVEL);

	ChangeLevel(LEVEL_TITLE_LEVEL);

}

void Worms::GameLoop()
{

}
void Worms::GameEnd()
{

}