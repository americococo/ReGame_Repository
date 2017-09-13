#include "DLinkedList.h"
#include "Array.h"
class Font;
class Track;
struct SDL_Texture;

class TrackMagent
{
public:
private:
	//DLinkedList<Track*> _trackList;
	Array<Track*> * _trckList;
	Font * _textFont;

private:
	int score;

public:
	TrackMagent();
	~TrackMagent();
	void AddTrack(int index,int W);

	void Render();
	void Update(int deltaTime);
	void DeInit();

	void keyDown(int keycode);
	void KeyUp(int keycode);

};