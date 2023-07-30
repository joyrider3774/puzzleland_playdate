#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../commonvars.h"
#include "coptionsselector.h"


COptionsSelector* COptionsSelector_Create()
{
	COptionsSelector* Result = (COptionsSelector *) malloc(sizeof(COptionsSelector));
	Result->Image = IMG_Load("./graphics/optionsselect.png");
	Result->Selection = 1;
	return Result;
}

void COptionsSelector_Draw(COptionsSelector* Selector)
{
	SDL_Rect aDstRect;
	switch(Selector->Selection)
	{
		case 1 :
			aDstRect.y = 40- (Selector->Image->h >> 2);
			break;
		case 2 :
			aDstRect.y = 60- (Selector->Image->h >> 2);
			break;
		case 3 :
			aDstRect.y = 80- (Selector->Image->h >> 2);
			break;
	}
	aDstRect.x = 100;
	aDstRect.w = Selector->Image->w;
	aDstRect.h = Selector->Image->h;
	SDL_BlitSurface(Selector->Image,NULL,Screen,&aDstRect);
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
		if(GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void COptionsSelector_MoveUp(COptionsSelector* Selector)
{
	if (Selector->Selection > 1)
	{
		Selector->Selection--;
		if(GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void COptionsSelector_Destroy(COptionsSelector* Selector)
{
	SDL_FreeSurface(Selector->Image);
	free(Selector);
}
