#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../gameobjects/ctitlescreenselector.h"
#include "../commonvars.h"
#include "titlescreen.h"

CTitleScreenSelector* TitleScreenSelector;

void TitleScreenInit()
{
	TitleScreenSelector = CTitleScreenSelector_Create();
	Background = loadImageAtPath("graphics/title");
	SelectMusic(musTitle);
}

void TitleScreenDeInit()
{
	pd->graphics->freeBitmap(Background);
	CTitleScreenSelector_destroy(TitleScreenSelector);
}

void TitleScreen()
{
	if(GameState == GSTitleScreenInit)
	{
		TitleScreenInit();
		GameState -= GSInitDiff;
	}

	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		CTitleScreenSelector_MoveUp(TitleScreenSelector);
	
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		CTitleScreenSelector_MoveDown(TitleScreenSelector);
	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		playMenuSelectSound();
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
	}
	//SDL_BlitSurface(Background,NULL,Screen,NULL);
	pd->graphics->clear(kColorWhite);
	pd->graphics->setBackgroundColor(kColorWhite);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
	
	CTitleScreenSelector_Draw(TitleScreenSelector);

	if(GameState != GSTitleScreen)
		TitleScreenDeInit();
}
