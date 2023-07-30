#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "../sound.h"
#include "coptionsselector.h"


COptionsSelector* COptionsSelector_Create()
{
	COptionsSelector* Result = pd->system->realloc(NULL, sizeof(COptionsSelector));
	Result->Image = loadImageAtPath("graphics/optionsselect");
	Result->Selection = 1;
	return Result;
}

void COptionsSelector_Draw(COptionsSelector* Selector)
{
	int y;
	switch(Selector->Selection)
	{
		case 1 :
			y = 65;
			break;
		case 2 :
			y = 95;
			break;
		case 3 :
			y = 125;
			break;
	}
	pd->graphics->drawBitmap(Selector->Image, 75, y, kBitmapUnflipped);
}

int COptionsSelector_GetSelection(COptionsSelector* Selector)
{
	return Selector->Selection;
}

void COptionsSelector_MoveDown(COptionsSelector* Selector)
{
	if (Selector->Selection < 2)
	{
		Selector->Selection++;
		playMenuSound();
	}
}

void COptionsSelector_MoveUp(COptionsSelector* Selector)
{
	if (Selector->Selection > 1)
	{
		Selector->Selection--;
		playMenuSound();
	}
}

void COptionsSelector_Destroy(COptionsSelector* Selector)
{
	pd->graphics->freeBitmap(Selector->Image);
	pd->system->realloc(Selector, 0);
}
