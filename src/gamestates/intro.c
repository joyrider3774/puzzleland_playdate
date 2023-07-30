#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "intro.h"

LCDBitmap *Pict1,*Pict2,*Pict3,*Pict4,*Pict5;
int Pictnr,Pictx,Picty;

void IntroInit()
{
	Pictx = WINDOW_WIDTH;
	Picty = WINDOW_HEIGHT;
	Pictnr = 1;
	Pict1 = pd->graphics->copyFrameBufferBitmap();
	Pict2 = loadImageAtPath("graphics/sdlpowered");
	Pict3 = loadImageAtPath("graphics/willemssoft");
	Pict4 = loadImageAtPath("graphics/title");
	Pict5 = pd->graphics->copyFrameBufferBitmap();
	//SDL_SetColorKey(Pict5,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(Pict5->format,255,0,255));
	//SDL_FillRect(Pict1,NULL,SDL_MapRGB(Pict1->format,0,0,0));
}

void IntroDeInit()
{
    pd->graphics->freeBitmap(Pict1);
    pd->graphics->freeBitmap(Pict2);
    pd->graphics->freeBitmap(Pict3);
    pd->graphics->freeBitmap(Pict4);
    pd->graphics->freeBitmap(Pict5);
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
		//SDL_Delay(2000);
		Pictx = 320;
		Picty = 120;
	}
	
	if(GameState == GSIntro)
	{
		if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) ||
			((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
			GameState = GSTitleScreenInit;

		if (currButtons & kButtonUp)
			showFps = true;

		switch(Pictnr)
		{
			case 1: //SDL_BlitSurface(Pict1,NULL,Screen,NULL);
					//SDL_BlitSurface(Pict2,NULL,Pict5,NULL);
					pd->graphics->drawBitmap(Pict1, 0, 0, kBitmapUnflipped);
					pd->graphics->pushContext(Pict5);
					pd->graphics->drawBitmap(Pict2, 0, 0, kBitmapUnflipped);
					pd->graphics->popContext();
					break;
			case 2: //SDL_BlitSurface(Pict2,NULL,Screen,NULL);
					//SDL_BlitSurface(Pict3,NULL,Pict5,NULL);
					pd->graphics->drawBitmap(Pict2, 0, 0, kBitmapUnflipped);
					pd->graphics->pushContext(Pict5);
					pd->graphics->drawBitmap(Pict3, 0, 0, kBitmapUnflipped);
					pd->graphics->popContext();
					break;
			case 3: //SDL_BlitSurface(Pict3,NULL,Screen,NULL);
					//SDL_BlitSurface(Pict4,NULL,Pict5,NULL);
					pd->graphics->drawBitmap(Pict3, 0, 0, kBitmapUnflipped);
					pd->graphics->pushContext(Pict5);
					pd->graphics->drawBitmap(Pict4, 0, 0, kBitmapUnflipped);
					pd->graphics->popContext();
					break;

		}
		//SDL_Rect aDstRect;
		//aDstRect.x = (int) 160 - Pictx/2;
		//aDstRect.y = (int) 120 - Picty/2;
		//aDstRect.w = Pictx;
		//aDstRect.h = Picty;
		//SDL_FillRect(Pict5,&aDstRect,SDL_MapRGB(Pict5->format,255,0,255));
		//SDL_BlitSurface(Pict5,NULL,Screen,NULL);
		pd->graphics->pushContext(Pict5);
		pd->graphics->fillRect((int)160 - Pictx / 2, (int)120 - Picty / 2, Pictx, Picty, kColorClear);
		pd->graphics->popContext();

		pd->graphics->clear(kColorWhite);
		pd->graphics->setBackgroundColor(kColorWhite);
		pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		
		pd->graphics->drawBitmap(Pict5, 0, 0, kBitmapUnflipped);
	}

	if(GameState != GSIntro)
		IntroDeInit();
}