#include <string.h>
#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../gameobjects/coptionsselector.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"
#include "options.h"

COptionsSelector* Selector;

void OptionsInit()
{
	CreateOtherMenuItems();
	Selector = COptionsSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void OptionsDeInit()
{
	pd->graphics->freeBitmap(Background);
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

	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
	{
		GameState = GSTitleScreenInit;
	}

	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		if (COptionsSelector_GetSelection(Selector) == 1)
			setSoundOn(!isSoundOn());
	
		if (COptionsSelector_GetSelection(Selector) == 2)
			setMusicOn(!isMusicOn());

		playMenuSelectSound();
	}
	
	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		COptionsSelector_MoveUp(Selector);
	
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		COptionsSelector_MoveDown(Selector);

	pd->graphics->clear(kColorWhite);
	pd->graphics->setBackgroundColor(kColorWhite);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	pd->graphics->pushContext(NULL);
	pd->graphics->setFont(Mini2X);

	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);

	int textw = pd->graphics->getTextWidth(Mini2X, "OPTIONS", strlen("OPTIONS"), kASCIIEncoding, 0);
	pd->graphics->drawText("OPTIONS", strlen("OPTIONS"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - (textw >> 1), 30);
	
	if (isSoundOn())
		pd->graphics->drawText("SOUND: ON", strlen("SOUND: ON"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 55, 70);
	else
		pd->graphics->drawText("SOUND: OFF", strlen("SOUND: OFF"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 55, 70);
	
	if (isMusicOn())
		pd->graphics->drawText("MUSIC: ON", strlen("MUSIC: ON"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 55, 100);
	else
		pd->graphics->drawText("MUSIC: OFF", strlen("MUSIC: OFF"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 55, 100);
	
	pd->graphics->popContext();

	COptionsSelector_Draw(Selector);

	if(GameState != GSOptions)
		OptionsDeInit();
}
