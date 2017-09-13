#pragma once
#include "GameObject.h"
class Sprite;

class Note:public gameObject
{
private:
	Sprite * _noteSprite;
	int _x,_y;
	int _updateDuration;
	int _start;

	bool _isLive;
	bool _isPass;
	int _judgeDeltaLine;

	int note_widthPostion;

public:
	Note(float natanamtime, int judgeDeltaLine);
	~Note();

	void Update(int deltaTime);
	void Render();
	void DeInit();
	void Init();

	bool IsLive();

	bool IsPass();
	void Pass();

	void UpdatePostion(int deltaTime);

	int getNoteTime();

	void setPostionWidth(int w);
};