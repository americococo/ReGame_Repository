#include "Note.h"
#include "Sprite.h"
#include "gameSystem.h"
#include "Track.h"
#include <stdio.h>

Note::Note(float natanamtime,int judgeDeltaLine)
{
	_noteSprite = NULL;
	_start = (GameSystem::Getinstance()->GetGameMoveTick() - (int)(natanamtime * 1000));
	_judgeDeltaLine = judgeDeltaLine;
	_isPass=false;
}

Note::~Note()
{
	
}
void Note::Update(int deltaTime) 
{
	_noteSprite->Update(deltaTime);
	
	UpdatePostion(deltaTime);
	/*int totalMoveTick =GameSystem::Getinstance()->GetGameMoveTick();
	int totalHeigh = GameSystem::Getinstance()->GetGameHeigh();

	_updateDuration = (_updateDuration + (deltaTime)) % totalMoveTick;
	float positionRate = ((float)_updateDuration / (float)totalMoveTick);

	float posioInSec = totalHeigh*positionRate;
	_y = (int)posioInSec - GameSystem::Getinstance()->GetWindowH() - 100;
*/
	_noteSprite->setPostion(_x, _y);

}
void Note::UpdatePostion(int deltaTime)
{

	_updateDuration += deltaTime;
	if (_updateDuration <= GameSystem::Getinstance()->GetGameMoveTick()+1000)
	{

		float positionRate = (float)_updateDuration / (float)GameSystem::Getinstance()->GetGameMoveTick();
		float positionSec = GameSystem::Getinstance()->GetGameHeigh()*positionRate;
		_y = positionSec - (GameSystem::Getinstance()->GetGameHeigh() - GameSystem::Getinstance()->GetWindowH()+_judgeDeltaLine);
	}
	else
	{
		_isLive = false;
		
	}
}
bool Note::IsLive()
{
	return _isLive;
}

bool Note::IsPass()
{
	return _isPass;
}

void Note::Pass()
{
	_isPass= true;
}

void Note::Render() 
{
	_noteSprite->Render();
}
void Note::DeInit()
{
	if (NULL != _noteSprite)
	{
		delete _noteSprite;
		_noteSprite = NULL;
	}
}
void Note::Init()
{
	_isLive = true;
	_noteSprite = new Sprite("note_sprite.csv",true);

	_x = (GameSystem::Getinstance()->GetWindowW() / 2);

	int gameTimeTick = GameSystem::Getinstance()->GetGameMoveTick();

	_updateDuration = _start;

	UpdatePostion(0);

	_noteSprite->setPostion(_x, _y);
}

int Note::getNoteTime()
{
	return _updateDuration;
}
void Note::setPostionWidth(int w)
{
	_x = (GameSystem::Getinstance()->GetWindowW() / 2)+w;
}