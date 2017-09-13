#include "Track.h"
#include "Note.h"
#include "Sprite.h"
#include"gameSystem.h"
#include"GameScene.h"
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Track::Track() 
{
	//_panjungsunSprite = NULL;
	//_trackSprite = NULL;
	//_explovisonSprite = NULL;
	_judge = ejudge::NONE;
	_updateDuration = 0;
}
Track::~Track() {}
	
void Track::Render() 
{

	{
		DLinkedListIterator<Sprite*> itr = backgroundSpriteList.GetIterator();
		for (itr.start(); itr.valid(); itr.Forth())
		{
			itr.item()->Render();
		}
	}

	DLinkedListIterator<Note*>  itr = _noteList.GetIterator();
	for (itr.start(); itr.valid(); itr.Forth())
		itr.item()->Render();

	_effectList->Get(effect::EXPLOSION)->Render();//0

	
}
void Track::Update(int deltaTime)
{
	_judgeTick = GameSystem::Getinstance()->GetGameMoveTick();
	_judgeStarTtick = _judgeTick - 200;
	_judgeEndTick = _judgeTick + 100;

	_updateDuration += deltaTime;
	{
		DLinkedListIterator<Sprite*> itr = backgroundSpriteList.GetIterator();
		for (itr.start(); itr.valid(); itr.Forth())
		{
			itr.item()->Update(deltaTime);
		}
	}

	_effectList->Get(effect::EXPLOSION)->Update(deltaTime);

	{
		DLinkedListIterator<Note*>  itr = _noteList.GetIterator();
		for (itr.start(); itr.valid(); itr.Forth())
		{
			if (itr.item()->IsLive())
			{
				itr.item()->Update(deltaTime);
			}
			else
			{
				delete itr.item();
				_noteList.Remove(itr);
			}

			if (_judgeEndTick < itr.item()->getNoteTime() && false != itr.item()->IsPass() && 
				GameSystem::Getinstance()->GetGameMoveTick()  > _updateDuration)//판정선을 한번만 지난거 판단
			{
				itr.item()->Pass();
				_judge = ejudge::FAIL;
				_noteList.Remove(itr);
			}
		}
	}
}
void Track::DeInit() 
{
	{
		DLinkedListIterator<Note*> itr = _noteList.GetIterator();
		for (itr.start(); itr.valid(); itr.Forth())
		{
			itr.item()->DeInit();
			//delete itr.item();
			_noteList.Remove(itr);
		}
	}
	{
		DLinkedListIterator<Sprite*> itr = backgroundSpriteList.GetIterator();
		for (itr.start(); itr.valid(); itr.Forth())
		{
			delete itr.item();
			backgroundSpriteList.Remove(itr);
		}
		
	}

	if (NULL != _effectList->Get(effect::EXPLOSION))
	{
		delete _effectList->Get(effect::EXPLOSION);
		_effectList->Remove(effect::EXPLOSION);
	}



}

void Track::Init() 
{
	_isKeyDown = false;
	_deltaLine = 100;


	char filePath[256];
	sprintf(filePath, "../Resource/%s", "TrackSetting.csv");

	FILE *fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("파일 오류 %s", filePath);
	}

	char TrackBackgroundName[256];
	char judgelineName[256];
	char ExplosionName[256];

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
				strcpy(TrackBackgroundName, token);
			}

			else if (!strcmp(token, "judgeline"))//strcmp 비교하는 두 값이 같으면 0을 반환
			{
				token = strtok(NULL, ",\n");
				strcpy(judgelineName, token);
			}

			else if (!strcmp(token, "Explosion"))//strcmp 비교하는 두 값이 같으면 0을 반환
			{
				token = strtok(NULL, ",\n");
				strcpy(ExplosionName, token);
			}
		}

	}
	fclose(fp);	

	Sprite * _trackSprite = new Sprite(TrackBackgroundName, true);
	_trackSprite->setPostion(GameSystem::Getinstance()->GetWindowW() / 2,GameSystem::Getinstance()->GetWindowH() / 2);

	Sprite * _panjungsunSprite = new Sprite(judgelineName , true);
	_panjungsunSprite->setPostion(GameSystem::Getinstance()->GetWindowW() / 2,GameSystem::Getinstance()->GetWindowH() - _deltaLine);

	backgroundSpriteList.apend(_trackSprite);
	backgroundSpriteList.apend(_panjungsunSprite);

	Sprite * _explovisonSprite = new Sprite(ExplosionName, false);
	_explovisonSprite->setPostion(GameSystem::Getinstance()->GetWindowW() / 2 ,GameSystem::Getinstance()->GetWindowH() - _deltaLine);

	
	_effectList = new Array<Sprite*>(1);
	_effectList->Set(effect::EXPLOSION, _explovisonSprite);




	
	int gameTime = GameSystem::Getinstance()->GetGameMoveTick();//존체 게임시갼
	int deltaTick = 0;

	for (int notetick= 0; notetick < gameTime;)
	{

		int randValue = rand() % 3;

		switch (randValue)
		{
		case 0:
			deltaTick = 250; break;
		case 1:
			deltaTick = 500; break;
		case 2:
			deltaTick = 750; break;
		default:
			deltaTick = 1000; break;
		}

		notetick += deltaTick;//게임전체시간에 맞춰서 끗냏
		float sec = (float)notetick / 1000.0f; 

		Note *note = new Note(sec,_deltaLine);
		note->Init();
		


		_noteList.apend(note);
	}

}

//노트판정
int Track::keyDown()
{
	if (_isKeyDown)
		return 0;

	_isKeyDown = true;

	_judge = ejudge::NONE;

	int score;

	DLinkedListIterator<Note*>  itr = _noteList.GetIterator();
	for (itr.start(); itr.valid(); itr.Forth())
	{
		if (itr.item()->getNoteTime() < _judgeStarTtick)
		{
			return 0;
		}
		//판정선내의 들어왔을때
		if (_judgeStarTtick <= itr.item()->getNoteTime() && itr.item()->getNoteTime() <= _judgeEndTick)
		{
			
			//_judge = ejudge::JUDGE;//판정선내에 들어왔는지 검사
			
			if (itr.item()->getNoteTime() >= _judgeTick+20 || itr.item()->getNoteTime() >= _judgeTick - 20)
			{
				_judge = ejudge::BEST;
				score = 50;
				break;
			}
			else if (itr.item()->getNoteTime() >= _judgeTick + 70 || itr.item()->getNoteTime() >= _judgeTick - 70)
			{
				_judge = ejudge::GOOD;
				score = 30;
				break;
			}

			else if (itr.item()->getNoteTime() >= _judgeEndTick || itr.item()->getNoteTime() >= _judgeStarTtick)
			{
				_judge = ejudge::BAD;
				score = 10;
				break;
			}
			
		}
	}
	switch (_judge)
	{
	case ejudge::GOOD:
		_effectList->Get(effect::EXPLOSION)->play();
		_noteList.Remove(itr);
		return score;
	case ejudge::BEST:
		_effectList->Get(effect::EXPLOSION)->play();
		_noteList.Remove(itr);
		return score;
	case ejudge::BAD:
		_effectList->Get(effect::EXPLOSION)->play();
		_noteList.Remove(itr);
		return score;
	case ejudge::NONE:
		_noteList.Remove(itr);
		return 0;
	default:
		_noteList.Remove(itr);
		return 0;
	}

}
void Track::KeyUp()
{
	_isKeyDown = false;


}
void Track::SetTrackpostion(int w)
{
	{
		DLinkedListIterator<Sprite*> itr = backgroundSpriteList.GetIterator();

		itr.start();
		itr.item()->setPostion(GameSystem::Getinstance()->GetWindowW() / 2 + w,
			GameSystem::Getinstance()->GetWindowH() / 2);

		itr.Forth();
		itr.item()->setPostion(GameSystem::Getinstance()->GetWindowW() / 2 + w,
			GameSystem::Getinstance()->GetWindowH() - _deltaLine);

		_effectList->Get(0)->setPostion(GameSystem::Getinstance()->GetWindowW() / 2 + w,
			GameSystem::Getinstance()->GetWindowH() - _deltaLine);

	}

	DLinkedListIterator<Note*>  itr = _noteList.GetIterator();
	for (itr.start(); itr.valid(); itr.Forth())
	{
		itr.item()->setPostionWidth(w);
	}
}