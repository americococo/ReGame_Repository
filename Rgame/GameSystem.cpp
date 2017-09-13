#include "gameSystem.h"
#include "SDL.h"
#include <stdio.h>

GameSystem* GameSystem::instance=NULL;

GameSystem::GameSystem()
{
	
}


GameSystem::~GameSystem()
{
	delete instance;
}


GameSystem* GameSystem::Getinstance()
{
	if (NULL == instance)
		instance = new GameSystem();

	return instance;
}

void GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}

int GameSystem::GetWindowW()
{
	return 1024;
}

int GameSystem::GetWindowH()
{
	return 800;
}

void GameSystem::setRender(SDL_Renderer* SDL_IPRender)
{
	_mRender= SDL_IPRender;
}

SDL_Renderer * GameSystem::GetRender()
{
	return _mRender;
}




void GameSystem::SetGameTime(float sec)
{
	_tick = (int)(sec * 1000.0f);
}

int GameSystem::GetGameMoveTick()
{
	return _tick;
}

void GameSystem::SetTrackHeigh(int heigh)
{
	_trackHeigh = heigh;
}


int GameSystem::GetGameHeigh()
{
	return _trackHeigh;
}
