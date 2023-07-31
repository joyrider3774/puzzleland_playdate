#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../commonvars.h"
#include "ctitlescreenselector.h"


CTitleScreenSelector* CTitleScreenSelector_Create()
{
	CTitleScreenSelector* Result = pd->system->realloc(NULL, sizeof(CTitleScreenSelector));
	Result->Image=loadImageAtPath("graphics/titleselector");
    Result->Selection = 1;
	return Result;
}

void CTitleScreenSelector_MoveUp(CTitleScreenSelector* selector)
{

	if (selector->Selection > 1)
	{
		selector->Selection--;
		playMenuSound();
	}

}

void CTitleScreenSelector_MoveDown(CTitleScreenSelector* selector)
{
	if (selector->Selection < 4)
	{
		selector->Selection++;
		playMenuSound();
	}

}

void CTitleScreenSelector_Draw(CTitleScreenSelector* selector)
{
	int y;
	switch (selector->Selection)
	{
		case 1 : y = 66;
				 break;
		case 2 : y = 100;
				 break;
		case 3 : y = 136;
				 break;
		case 4 : y = 175;
				 break;
	}
	pd->graphics->drawBitmap(selector->Image, 71, y, kBitmapUnflipped);
}

void CTitleScreenSelector_destroy(CTitleScreenSelector* selector)
{
	pd->graphics->freeBitmap(selector->Image);
	pd->system->realloc(selector, 0);
}

