#pragma once
#include "GameObject.h"
#include "DLinkedList.h"

#include "Scene.h"

class Note;

class Sprite;
class TrackMagent;
struct SDL_Texture;
class Font;

class GameScene : public Scene
{
private:
	DLinkedList<Note*> _noteList;
	Sprite * _backGroundSprite;

	TrackMagent *TM;
	int _gameDuration;
public:
	GameScene();
	~GameScene();

	void Render();
	void Update(int deltaTime);
	void DeInit();
	void Init();
	void keyDown(int keycode);
	void KeyUp(int keycode);

};