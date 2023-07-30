#include <SDL.h>
#include <SDL_image.h>
#include "../gameobjects/coptionsselector.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "options.h"

COptionsSelector* Selector;

void OptionsInit()
{
	Selector = COptionsSelector_Create();
	Background = IMG_Load("./graphics/paper.png");
	SDL_PollEvent(&Event);
}

void OptionsDeInit()
{
	SDL_FreeSurface(Background);
	COptionsSelector_Destroy(Selector);
	SaveSettings();
}

void Options()
{

	if(GameState == GSOptionsInit)
	{
		OptionsInit();
		GameState -= GSInitDiff;
	}

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_KEYDOWN)
		{
			switch (Event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					GameState = GSTitleScreenInit;
					break;
				case SDLK_x:
					if(COptionsSelector_GetSelection(Selector) == 1)
						SoundEnabled = ! SoundEnabled;
					if(COptionsSelector_GetSelection(Selector) == 2)
					{
						MusicEnabled = ! MusicEnabled;
						if (!MusicEnabled)
							Mix_HaltMusic();
						else
							Mix_PlayMusic(Music[MUS_Title],-1);
					}
					if(GlobalSoundEnabled && SoundEnabled)
						Mix_PlayChannel(-1,Sounds[SND_Select],0);
					break;
				case SDLK_UP:
					COptionsSelector_MoveUp(Selector);
					break;
				case SDLK_DOWN:
					COptionsSelector_MoveDown(Selector);
					break;
				default:
					break;
			}

		}
	}
	SDL_BlitSurface(Background,NULL,Screen,NULL);
	TTF_SetFontStyle(font,TTF_STYLE_UNDERLINE);
	SDL_Color Color1 = {0,0,0,0};
	WriteText(Screen,font,"OPTIONS",7,Screen->w / 2 - 25,20,0,Color1);
	TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
	char Msg[20];
	if(SoundEnabled)
		strcpy(Msg,"SOUND: ON");
	else
		strcpy(Msg,"SOUND: OFF");
	WriteText(Screen,font,Msg,strlen(Msg),Screen->w / 2 -35,40,0,Color1);
	if (MusicEnabled)
		strcpy(Msg,"MUSIC: ON");
	else
		strcpy(Msg,"MUSIC: OFF");
	WriteText(Screen,font,Msg,strlen(Msg),Screen->w / 2 -35,60,0,Color1);
	COptionsSelector_Draw(Selector);

	if(GameState != GSOptions)
		OptionsDeInit();
}
