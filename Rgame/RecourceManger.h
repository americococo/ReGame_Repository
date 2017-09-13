#pragma once

#include <iostream>//stl를 사용하기위한 헤더
#include <map>
#include <string>


#include "SDL.h"
#include "SDL_image.h"

class RecourceManger
{
private:
	static RecourceManger* instance;

	RecourceManger();
public:
	~RecourceManger();

public:
	static RecourceManger*  GetInstance();


private:
	std::map<std::string, SDL_Texture *> _TextureMap; //stl네임스페이스의 map를 사용 (char * 키값을 사용해 SDL_Texture를 차즘(고유값))	

public:
	SDL_Texture * FindTexture(std::string  fileName);
};