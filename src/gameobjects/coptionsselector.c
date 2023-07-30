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
	//SDL_Rect aDstRect;
	int y = 0;
	int h = 0;
	pd->graphics->getBitmapData(Selector->Image, NULL, &h, NULL, NULL, NULL);
	switch(Selector->Selection)
	{
		case 1 :
			y = 40- (h >> 2);
			break;
		case 2 :
			y = 60- (h >> 2);
			break;
		case 3 :
			y = 80- (h >> 2);
			break;
	}
	/*aDstRect.x = 100;
	aDstRect.w = Selector->Image->w;
	aDstRect.h = Selector->Image->h;
	SDL_BlitSurface(Selector->Image,NULL,Screen,&aDstRect);*/
	pd->graphics->drawBitmap(Selector->Image, 100, y, kBitmapUnflipped);
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
