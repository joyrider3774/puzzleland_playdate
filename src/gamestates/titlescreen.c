#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../gameobjects/ctitlescreenselector.h"
#include "../commonvars.h"
#include "titlescreen.h"

CTitleScreenSelector* TitleScreenSelector;

void TitleScreenInit()
{
	TitleScreenSelector = CTitleScreenSelector_Create();
	SDL_PollEvent(&Event);
	Background = IMG_Load("./graphics/title.png");
	if (GlobalSoundEnabled && MusicEnabled && (Mix_PlayingMusic() == 0))  Mix_PlayMusic(Music[MUS_Title],-1);
}

void TitleScreenDeInit()
{
	SDL_FreeSurface(Background);
	CTitleScreenSelector_destroy(TitleScreenSelector);
}

void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSInitDiff;
	}

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_KEYDOWN)
		{
			switch (Event.key.keysym.sym)
			{

				case SDLK_ESCAPE:
					GameState = GSQuit;
					break;
				case SDLK_UP :
					CTitleScreenSelector_MoveUp(TitleScreenSelector);
					break;
				case SDLK_DOWN :
					CTitleScreenSelector_MoveDown(TitleScreenSelector);
					break;
				case SDLK_x:
					if (GlobalSoundEnabled & SoundEnabled) Mix_PlayChannel(-1,Sounds[SND_Select],0);
					switch (TitleScreenSelector->Selection)
					{
						case 1:
							Level = 0;
							GameState = GSOldManSpeakingInit;
							break;
						case 2:
							GameState = GSPasswordEntryInit;
							break;
						case 3:
							GameState = GSOptionsInit;
							break;
						case 4:
							GameState = GSCreditsInit;
							break;
					}
				default:
					break;
			}
		}
	}
	SDL_BlitSurface(Background,NULL,Screen,NULL);
	CTitleScreenSelector_Draw(TitleScreenSelector);

	if(GameState != GSTitleScreen)
		TitleScreenDeInit();
}
