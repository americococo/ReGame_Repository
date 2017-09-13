#include "Font.h"
#include "gameSystem.h"
#include "SDL_ttf.h"
#include <stdio.h>

Font::Font(const char * fileName, int fontSize)
{
	char filePaht[256];
	sprintf(filePaht, "../Resource/Font/%s", fileName);

	_sansFont = TTF_OpenFont(filePaht, fontSize);

}
Font::~Font()
{

}
void Font::setText(const char * text)
{
	SDL_Color Black = { 0,0,0 };
	SDL_Surface * surfaceMessage = TTF_RenderText_Solid(_sansFont, text, Black);
	_texture = SDL_CreateTextureFromSurface(GameSystem::Getinstance()->GetRender(), surfaceMessage);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	{
		_srcRect.x = 0;
		_srcRect.y = 0;

		_destRect.w = _srcRect.w;
		_destRect.h = _srcRect.h;
	}

}