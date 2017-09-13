#include "Texture.h"
#include "SDL_ttf.h"

class Font :public Texture
{
public:
	Font(const char * fileName,int fontSize);
	~Font();
	void setText(const char *text);

private:
	TTF_Font *  _sansFont;
};