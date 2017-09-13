#include "RecourceManger.h"
#include "gameSystem.h"
using namespace std;

#include <stdio.h>

RecourceManger * RecourceManger::instance =NULL;

RecourceManger::RecourceManger(){}

RecourceManger* RecourceManger::GetInstance()
{
	if (NULL == instance)
		instance = new RecourceManger();

	return  instance;
}


RecourceManger::~RecourceManger()
{
	map<string, SDL_Texture*>::iterator it;
	for (it = _TextureMap.begin(); it != _TextureMap.end(); it++)
	{
		delete it->second;
	}

	_TextureMap.clear();//싹다 지움 
}


SDL_Texture * RecourceManger::FindTexture(string fileName)
{
	//탐색
	map<string, SDL_Texture*>::iterator it = _TextureMap.find(fileName);//반복자를 돌리면서 fileName  fnf
	if (it != _TextureMap.end())//맨마지막에 도달하면 못찾았다 마지막 값은 NULL
	{
		return it->second;
	}

	SDL_Texture * _texture = IMG_LoadTexture(GameSystem::Getinstance()->GetRender(), fileName.c_str()/*c_str- string 울 char 형으로 반환*/);

	_TextureMap[fileName/*키값*/] = _texture;

	return _texture;
}