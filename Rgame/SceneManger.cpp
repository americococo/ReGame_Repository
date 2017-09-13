#include "SceneManger.h"
#include "Scene.h"
#include "tiltleScene.h"
#include "GameScene.h"
#include <stdio.h>

SceneManger* SceneManger::instance = NULL;

SceneManger::SceneManger() 
{
	_Scene = NULL;
}
SceneManger::~SceneManger()
{
	if (NULL != _Scene)//종료시 마지막 씬
	{
		_Scene->DeInit();
	}
}

SceneManger * SceneManger::Getinstance()
{
	if (instance == NULL)
		instance= new SceneManger();
	return  instance;
}

void SceneManger::ChangeScene(int SceneType) 
{
	if (NULL != _Scene)
	{
		_Scene->DeInit();
		delete _Scene;
	}

	switch (SceneType)
	{
	case SceneType::GAME:
		_Scene = new GameScene();
		break;
	case SceneType::TITITLE:
		_Scene = new TitleScene();
		break;
	}

	_Scene->Init();
}
void SceneManger::KeyUp(int keycode) 
{
	_Scene->KeyUp(keycode);
}
void SceneManger::keyDown(int keycode) 
{
	_Scene->keyDown(keycode);
}
void SceneManger::Update(int deltaTime)
{
	_Scene->Update(deltaTime);
}
void SceneManger::Render() 
{
	_Scene->Render();
}