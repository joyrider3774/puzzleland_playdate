#include <SDL.h>
#include <SDL_mixer.h>
#include "../commonvars.h"
#include "gamecommon.h"
#include "stageclear.h"


bool KaderVisible;

void StageClearInit()
{
	KaderVisible = true;
 	SDL_PollEvent(&Event);
}

void StageClearDeInit()
{

}

void StageClear()
{
	if(GameState == GSStageClearInit)
	{
		StageClearInit();
		GameState -= GSInitDiff;
	}

 	 while(SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_KEYDOWN)
		{
			switch(Event.key.keysym.sym)
			{
				case SDLK_ESCAPE :
					Mix_HaltChannel(0);
					Mix_HaltChannel(1);
					Mix_HaltMusic();
					GameState = GSTitleScreenInit;
					break;
				case SDLK_x :
					Mix_HaltChannel(0);
					Mix_HaltChannel(1);
					Mix_HaltMusic();
					GameState = GSOldManSpeakingInit;
					break;
				case SDLK_c:
					KaderVisible = !KaderVisible;
					break;
				default:
					break;
			}
		}
	}
	SDL_Rect aDstRect;
	aDstRect.x = XOffsetGame-4;
	aDstRect.y = YOffsetGame + 75;
	aDstRect.w = StageClearKader->w;
	aDstRect.h = StageClearKader->h;
	SDL_BlitSurface(RoomBackground,NULL,Screen,NULL);
	DrawPanel();
	DrawPlayField();
	if (KaderVisible)
		SDL_BlitSurface(StageClearKader,NULL,Screen,&aDstRect);

	if(GameState != GSStageClear)
		StageClearDeInit();
}
