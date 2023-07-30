#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../commonvars.h"
#include "ctitlescreenselector.h"


CTitleScreenSelector* CTitleScreenSelector_Create()
{
	CTitleScreenSelector* Result = (CTitleScreenSelector *) malloc(sizeof(CTitleScreenSelector));
	Result->Image=IMG_Load("./graphics/titleselector.png");
    Result->Selection = 1;
	return Result;
}

void CTitleScreenSelector_MoveUp(CTitleScreenSelector* selector)
{

	if (selector->Selection > 1)
	{
		selector->Selection--;
		if(GlobalSoundEnabled && SoundEnabled) Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}

}

void CTitleScreenSelector_MoveDown(CTitleScreenSelector* selector)
{
	if (selector->Selection < 4)
	{
		selector->Selection++;
		if(GlobalSoundEnabled && SoundEnabled) Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}

}

void CTitleScreenSelector_Draw(CTitleScreenSelector* selector)
{
	SDL_Rect aDstRect;
	switch (selector->Selection)
	{
		case 1 : aDstRect.y = 66;
				 break;
		case 2 : aDstRect.y = 100;
				 break;
		case 3 : aDstRect.y = 136;
				 break;
		case 4 : aDstRect.y = 175;
				 break;
	}
	aDstRect.x = 71;
	aDstRect.w = selector->Image->w;
	aDstRect.h = selector->Image->h;
	SDL_BlitSurface(selector->Image,NULL,Screen,&aDstRect);
}

void CTitleScreenSelector_destroy(CTitleScreenSelector* selector)
{
	SDL_FreeSurface(selector->Image);
	free(selector);
}

