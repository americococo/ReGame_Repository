#include "TrackMagent.h"
#include "Track.h"
#include "SDL.h"
#include "Font.h"
#include "SDL_ttf.h"
#include "Texture.h"

TrackMagent::TrackMagent()
{
	_textFont = NULL;

	_textFont = new Font("arialbd.ttf", 24);

	score = 0;

	char text[256];
	sprintf(text, "score:%d", score);
	_textFont->setText(text);
	_textFont->setPosition(100, 50);

	_trckList = new Array<Track*>(2);
	
}
TrackMagent::~TrackMagent() {}

void TrackMagent::AddTrack(int index,int W)
{
	Track * track = new Track();
	track->Init();

	track->SetTrackpostion(W);

	_trckList->Set(index, track);

}
void TrackMagent::Render()
{
	_textFont->Render();

	/*DLinkedListIterator<Track*> itr= _trackList.GetIterator();
	for (itr.start(); itr.valid(); itr.Forth())
	{
		itr.item()->Render();
	}*/

	for (int i = 0; i < _trckList->sizeGet(); i++)
	{
		_trckList->Get(i)->Render();
	}
	
}
void TrackMagent::Update(int deltaTime)
{

	for (int i = 0; i < _trckList->sizeGet(); i++)
	{
		_trckList->Get(i)->Update(deltaTime);
	}

	char text[256];
	sprintf(text, "score:%d", score);
	_textFont->setText(text);
	_textFont->setPosition(100, 50);

}
void TrackMagent::DeInit()
{

	for (int i = 0; i < _trckList->sizeGet(); i++)
	{
		_trckList->Get(i)->DeInit();
		//_trckList->Remove(0);
	}

	if (NULL != _textFont)
	{
		delete _textFont;
		_textFont = NULL;
	}

}

void TrackMagent::keyDown(int keycode)
{
	char text[256];

	switch (keycode)
	{
	case SDLK_LSHIFT:
		score+= _trckList->Get(0)->keyDown();
		break;
	case SDLK_SPACE:
		score += _trckList->Get(1)->keyDown();
		break;
	default:
		break;
	}

}

void TrackMagent::KeyUp(int keycode)
{

	switch (keycode)
	{
	case SDLK_LSHIFT:
	_trckList->Get(0)->KeyUp(); break;
	case SDLK_SPACE:
	_trckList->Get(1)->KeyUp(); break;
	default:
		break;
	}
}