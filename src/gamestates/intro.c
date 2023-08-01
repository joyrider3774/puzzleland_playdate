#include <pd_api.h>
#include "gamecommon.h"
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "intro.h"

LCDBitmap *Pict1,*Pict2,*Pict3,*Pict5, *Pict6;
int Pictnr,Pictx,Picty, screenDelay = 0;

void IntroInit()
{
	Pictx = WINDOW_WIDTH;
	Picty = WINDOW_HEIGHT;
	Pictnr = 1;
	Pict1 = pd->graphics->copyFrameBufferBitmap();
	pd->graphics->pushContext(Pict1);
	pd->graphics->clear(kColorBlack);
	pd->graphics->popContext();
	Pict2 = loadImageAtPath("graphics/intro");
	Pict3 = loadImageAtPath("graphics/title");
	Pict5 = pd->graphics->copyFrameBufferBitmap();
	Pict6 = pd->graphics->copyFrameBufferBitmap();
	CreateOtherMenuItems();
}

void IntroDeInit()
{
    pd->graphics->freeBitmap(Pict1);
    pd->graphics->freeBitmap(Pict2);
    pd->graphics->freeBitmap(Pict3);
    pd->graphics->freeBitmap(Pict5);
	pd->graphics->freeBitmap(Pict6);
}

void Intro()
{
    if(GameState == GSIntroInit)
	{
		IntroInit();
		GameState -= GSInitDiff;
	}

	if (screenDelay > 0)
		screenDelay--;
	
	if (screenDelay == 0)
	{
		Pictx -= 10;
		if (Picty > 0)
		{
			Picty -= 10;
		}
		else
		{
			screenDelay = FRAMERATE;
			Pictnr++;
			if (Pictnr == 3)
			{
				GameState = GSTitleScreenInit;
			}
			else
				Pictx = WINDOW_WIDTH;
			Picty = WINDOW_HEIGHT;
		}
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
			case 1: pd->graphics->drawBitmap(Pict1, 0, 0, kBitmapUnflipped);
					pd->graphics->pushContext(Pict5);
					pd->graphics->drawBitmap(Pict2, 0, 0, kBitmapUnflipped);
					pd->graphics->popContext();
					break;
			case 2: pd->graphics->drawBitmap(Pict2, 0, 0, kBitmapUnflipped);
					pd->graphics->pushContext(Pict5);
					pd->graphics->drawBitmap(Pict3, 0, 0, kBitmapUnflipped);
					pd->graphics->popContext();
					break;

		}
		pd->graphics->pushContext(Pict6);
		pd->graphics->clear(kColorWhite);
		pd->graphics->fillRect((int)160 - Pictx / 2, (int)120 - Picty / 2, Pictx, Picty, kColorBlack);
		pd->graphics->popContext();

		pd->graphics->setBitmapMask(Pict5, Pict6);
		pd->graphics->drawBitmap(Pict5, 0, 0, kBitmapUnflipped);
	}

	if(GameState != GSIntro)
		IntroDeInit();
}