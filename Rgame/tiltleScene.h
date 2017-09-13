#pragma once
#include "Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Render();
	void Update(int deltaTime);
	void DeInit();
	void Init();
};