#pragma once
#include "DLinkedList.h"
#include "GameObject.h"
#include "Array.h"
class Note;
class Sprite;

enum ejudge
{
	NONE,
	GOOD,
	BEST,
	BAD,
	FAIL
};

class Track: public gameObject
{
public:
	enum effect
	{
		EXPLOSION
	};

private:
	DLinkedList<Note*> _noteList;

	DLinkedList<Sprite*> backgroundSpriteList;

	
	Array<Sprite*> * _effectList;

	int _updateDuration;

	int _judgeTick;
	int _judgeStarTtick;
	int _judgeEndTick;

	bool _isKeyDown;

	ejudge _judge;
	
	int _deltaLine;
public:
	Track();
	~Track();

	void Render();
	void Update(int deltaTime);
	void DeInit();
	void Init();

public:
	//Å°ÀÔ·Â
	int keyDown();
	void KeyUp();

public:

	void SetTrackpostion(int w);
};

