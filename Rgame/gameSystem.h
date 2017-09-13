#pragma once

struct SDL_Renderer;
struct SDL_Window;


class GameSystem
{
	//singleTon 하나의 instance만을 사용	
private:
	static GameSystem* instance;
	SDL_Renderer * _mRender;

public:
	static GameSystem * Getinstance();


	void setRender(SDL_Renderer * SDL_IPRender);
	SDL_Renderer * GetRender();

	//window Info
public:
	int GetWindowW();
	int GetWindowH();

	//Gameinfo
private:
	int _trackHeigh;
	int _tick;

public:

	void SetGameTime(float sec);
	int GetGameMoveTick();

	void SetTrackHeigh(int heigh);
	int GetGameHeigh();

	//Quit
public:
	void Quit();

private:
	GameSystem();

public:
	~GameSystem();
};
