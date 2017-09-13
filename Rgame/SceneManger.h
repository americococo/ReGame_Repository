#pragma once
class Scene;
enum SceneType
{
	TITITLE,
	GAME
};


class SceneManger
{
private:
	static SceneManger * instance;
	SceneManger();
public:
	~SceneManger();
	static SceneManger * Getinstance();

private:
	Scene * _Scene;
public:
	void ChangeScene(int SceneType);
	void KeyUp(int keycode);
	void keyDown(int keycode);
	void Update(int deltaTime);
	void Render();
};