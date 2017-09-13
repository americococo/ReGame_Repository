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

	_TextureMap.clear();//�ϴ� ���� 
}


SDL_Texture * RecourceManger::FindTexture(string fileName)
{
	//Ž��
	map<string, SDL_Texture*>::iterator it = _TextureMap.find(fileName);//�ݺ��ڸ� �����鼭 fileName  fnf
	if (it != _TextureMap.end())//�Ǹ������� �����ϸ� ��ã�Ҵ� ������ ���� NULL
	{
		return it->second;
	}

	SDL_Texture * _texture = IMG_LoadTexture(GameSystem::Getinstance()->GetRender(), fileName.c_str()/*c_str- string �� char ������ ��ȯ*/);

	_TextureMap[fileName/*Ű��*/] = _texture;

	return _texture;
}