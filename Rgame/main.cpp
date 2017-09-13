#include "SDL.h"
#include "SDL_image.h"
#include "gameSystem.h"
#include "Sprite.h"
#include "Note.h"
#include "GameScene.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "tiltleScene.h"
#include "SceneManger.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	if (TTF_Init() != 0)
	{
		printf("errer");
	}
	atexit(TTF_Quit);

	GameSystem* gS = GameSystem::Getinstance();

	int Window_w = gS->GetWindowW();
	int Window_h = gS->GetWindowH();

	SDL_Window * SDL_win = SDL_CreateWindow("Redm game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_w, Window_h, SDL_WINDOW_OPENGL);

	SDL_Renderer *_mRender = SDL_CreateRenderer(SDL_win, 0, 0);

	gS->setRender(_mRender);



	SceneManger::Getinstance()->ChangeScene(SceneType::TITITLE);

	SDL_SetRenderDrawColor(gS->GetRender(), 255, 255, 255, 255);


	int y = 0;

	SDL_Event Event;

	int frame = 0, oldFrame = 0;
	int curtick = SDL_GetTicks();
	int oldTick = curtick;

	while (1)
	{
		curtick = SDL_GetTicks();//

		frame = (SDL_GetTicks() % 1000) * 60;

		frame /= 1000;

		if (oldFrame != frame)
		{
			oldFrame = frame;

			int deltaTime = curtick - oldTick;
			oldTick = curtick;

			if (SDL_PollEvent(&Event))
			{
				if (SDL_QUIT == Event.type)
					break;

				if (SDL_KEYUP == Event.type)
				{
					if (Event.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Event quitEvent;
						quitEvent.type = SDL_QUIT;
						SDL_PushEvent(&quitEvent);
					}
					SceneManger::Getinstance()->KeyUp(Event.key.keysym.sym);
				}

				if (SDL_KEYDOWN == Event.type)
				{
					SceneManger::Getinstance()->keyDown(Event.key.keysym.sym);
				}
			}

			SceneManger::Getinstance()->Update(deltaTime);

			SDL_RenderClear(gS->GetRender());
			{
				SceneManger::Getinstance()->Render();
			}

			SDL_RenderPresent(gS->GetRender());
		}
	}

	SDL_DestroyRenderer(gS->GetRender());


	return 0;
}