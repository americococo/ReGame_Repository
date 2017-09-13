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
		printf("���� ���� %s", filePath);
	}

	//������ �ޱ� ���� ����
	char backgroundSpriteName[256];
	char musicFileName[256];
	float gametimemin;

	char buffer[1024];
	char * record = fgets(buffer, sizeof(buffer), fp);

	while (true)//���� �����ɰ�� ��� 
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		
		{
			char * token = strtok(record, ",\n");
			if (!strcmp(token, "Background"))//strcmp ���ϴ� �� ���� ������ 0�� ��ȯ
			{
				token = strtok(NULL, ",\n");
				strcpy(backgroundSpriteName, token);
			}

			else if (!strcmp(token, "MusicName"))//strcmp ���ϴ� �� ���� ������ 0�� ��ȯ
			{
				token = strtok(NULL, ",\n");
				strcpy(musicFileName, token);
			}

			else if (!strcmp(token, "playTime"))//strcmp ���ϴ� �� ���� ������ 0�� ��ȯ
			{
				token = strtok(NULL, ",\n");
				gametimemin = atof(token);
			}
		}

	}

	fclose(fp);	

	int bpm = 60*2;//�ӵ�����(�⺻ �ӵ�)
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

	//���� pl����
	int result = Mix_Init(MIX_INIT_MP3);//mp3�� ����ϱ����� �ʱ�ȭ
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
			printf("load ������;;;");
		}

	}

	else
	{
		printf("mp3���� ������;;");
	}
}

void GameScene::Render() 
{
	_backGroundSprite->Render();

	TM->Render();

}
void GameScene::Update(int deltaTime)
{


	if (_gameDuration < GameSystem::Getinstance()->GetGameMoveTick()+1000)//��Ʈ�� ������ ������ ���������� 
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


