#pragma once
#include "GameObject.h"

class Scene:public gameObject
{
public:
	Scene();
	~Scene();

	void Render();
	void Update(int deltaTime);
	void DeInit();
	void Init();
	virtual void keyDown(int keycode);
	virtual void KeyUp(int keycode);

};