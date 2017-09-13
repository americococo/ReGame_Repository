#include "GameScene.h"

#include "gameSystem.h"

#include "Note.h"
#include "Track.h"
#include "TrackMagent.h"	
#include "Sprite.h"

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <string.h>

GameScene::GameScene()
{
	_backGroundSprite = NULL;
}

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	char filePath[256];
	sprintf(filePath, "../Resource/%s", "gameplay.csv");

	FILE *fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("파일 오류 %s", filePath);
	}

	//데이터 받기 위한 공간
	char backgroundSpriteName[256];
	char musicFileName[256];
	float gametimemin;

	char buffer[1024];
	char * record = fgets(buffer, sizeof(buffer), fp);

	while (true)//값이 고정될경우 사용 
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		
		{
			char * token = strtok(record, ",\n");
			if (!strcmp(token, "Background"))//strcmp 비교하는 두 값이 같으면 0을 반환
			{
				token = strtok(NULL, ",\n");
				strcpy(backgroundSpriteName, token);
			}

			else if (!strcmp(token, "MusicName"))//strcmp 비교하는 두 값이 같으면 0을 반환
			{
				token = strtok(NULL, ",\n");
				strcpy(musicFileName, token);
			}

			else if (!strcmp(token, "playTime"))//strcmp 비교하는 두 값이 같으면 0을 반환
			{
				token = strtok(NULL, ",\n");
				gametimemin = atof(token);
			}
		}

	}

	fclose(fp);	

	int bpm = 60*2;//속도조절(기본 속도)
	int tempo = bpm / 60;

	float gametime = gametimemin*60.0f;
	int trackheight = GameSystem::Getinstance()->GetWindowH()*(gametime*tempo);

	GameSystem::Getinstance()->SetGameTime(gametime);
	GameSystem::Getinstance()->SetTrackHeigh(trackheight);

	_backGroundSprite = new Sprite(backgroundSpriteName,true);

	_backGroundSprite->setPostion(GameSystem::Getinstance()->GetWindowW() / 2, GameSystem::Getinstance()->GetWindowH() / 2);

	TM = new TrackMagent();
	int TM_index = 0;
		TM->AddTrack(TM_index,-150); TM_index++;
		TM->AddTrack(TM_index,150);
	
	_gameDuration = 0;

	//음악 pl레이
	int result = Mix_Init(MIX_INIT_MP3);//mp3를 사용하기위해 초기화
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

		char musicfilePath[256];
		sprintf(musicfilePath, "../Resource/music/%s",musicFileName);

		Mix_Music * music = Mix_LoadMUS(musicfilePath);
		if (NULL != music)
		{
			Mix_PlayMusic(music, 0);

		}
		else
		{
			printf("load 못했음;;;");
		}

	}

	else
	{
		printf("mp3파일 못읽음;;");
	}
}

void GameScene::Render() 
{
	_backGroundSprite->Render();

	TM->Render();

}
void GameScene::Update(int deltaTime)
{


	if (_gameDuration < GameSystem::Getinstance()->GetGameMoveTick()+1000)//노트가 끗까지 오고난후 끗나기위해 
	{
		_backGroundSprite->Update(deltaTime);
		
		_gameDuration += deltaTime;

		TM->Update(deltaTime);

	}

	else
	{
		GameSystem::Getinstance()->Quit();
	}


}
void GameScene::DeInit() 
{
	if (NULL != _backGroundSprite)
	{
		delete _backGroundSprite;
		_backGroundSprite = NULL;
	}
	TM->DeInit();

}


void  GameScene::keyDown(int keycode)
{

	switch (keycode)
	{
	case SDLK_LSHIFT:
		TM->keyDown(SDLK_LSHIFT);  break;
	case SDLK_SPACE:
		TM->keyDown(SDLK_SPACE);break;
	default:
		break;
	}

}
void GameScene::KeyUp(int keycode)
{

	switch (keycode)
	{
	case SDLK_LSHIFT:
		TM->KeyUp(SDLK_LSHIFT);  break;

	case SDLK_SPACE:
		TM->KeyUp(SDLK_SPACE);  break;
	default:
		break;
	}
}


