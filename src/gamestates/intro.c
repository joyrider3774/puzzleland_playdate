#include <SDL.h>
#include <SDL_image.h>
#include "../commonvars.h"
#include "intro.h"

SDL_Surface *Pict1,*Pict2,*Pict3,*Pict4,*Pict5;
int Pictnr,Pictx,Picty;

void IntroInit()
{
	Pictx = WINDOW_WIDTH;
	Picty = WINDOW_HEIGHT;
	Pictnr = 1;
	Pict1 = SDL_DisplayFormat(Screen);
	Pict2 = IMG_Load("./graphics/sdlpowered.png");
	Pict3 = IMG_Load("./graphics/willemssoft.png");
	Pict4 = IMG_Load("./graphics/title.png");
	Pict5 = SDL_DisplayFormat(Screen);
	SDL_SetColorKey(Pict5,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(Pict5->format,255,0,255));
	SDL_FillRect(Pict1,NULL,SDL_MapRGB(Pict1->format,0,0,0));
    SDL_PollEvent(&Event);
}

void IntroDeInit()
{
    SDL_FreeSurface(Pict1);
    SDL_FreeSurface(Pict2);
    SDL_FreeSurface(Pict3);
    SDL_FreeSurface(Pict4);
    SDL_FreeSurface(Pict5);
    SDL_PollEvent(&Event);
}

void Intro()
{
    if(GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSInitDiff;
	}
	
	Pictx -= 20;
	if (Picty >0)
	{
		Picty -= 15;
	}
	else
	{
		Pictnr++;
		if (Pictnr == 4)
		{
			GameState = GSTitleScreenInit;
		}
		else
		SDL_Delay(2000);
		Pictx = 320;
		Picty = 120;
	}
	
	if(GameState == GSIntro)
	{
		while(SDL_PollEvent(&Event))
		{
			switch(Event.type)
			{
				case SDL_KEYDOWN :
					if (Event.key.keysym.sym == SDLK_ESCAPE)
					{
						GameState = GSQuit;
					}
					else
					{
						GameState = GSTitleScreenInit;
					}
			}
		}
		switch(Pictnr)
		{
			case 1: SDL_BlitSurface(Pict1,NULL,Screen,NULL);
					SDL_BlitSurface(Pict2,NULL,Pict5,NULL);
					break;
			case 2: SDL_BlitSurface(Pict2,NULL,Screen,NULL);
					SDL_BlitSurface(Pict3,NULL,Pict5,NULL);
					break;
			case 3: SDL_BlitSurface(Pict3,NULL,Screen,NULL);
					SDL_BlitSurface(Pict4,NULL,Pict5,NULL);
					break;

		}
		SDL_Rect aDstRect;
		aDstRect.x = (int) 160 - Pictx/2;
		aDstRect.y = (int) 120 - Picty/2;
		aDstRect.w = Pictx;
		aDstRect.h = Picty;
		SDL_FillRect(Pict5,&aDstRect,SDL_MapRGB(Pict5->format,255,0,255));
		SDL_BlitSurface(Pict5,NULL,Screen,NULL);
	}

	if(GameState != GSIntro)
		IntroDeInit();
}