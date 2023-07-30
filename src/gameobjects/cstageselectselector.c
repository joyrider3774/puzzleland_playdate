#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../commonvars.h"
#include "cstageselectselector.h"


CStageSelectSelector* CStageSelectSelector_Create()
{
	CStageSelectSelector* Result = (CStageSelectSelector *) malloc(sizeof(CStageSelectSelector));
	Result->Image=IMG_Load("./graphics/select.png");
    Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CStageSelectSelector_Draw(CStageSelectSelector* selector)
{
	SDL_Rect aDstRect;
	aDstRect.x = XOffsetStageSelect + selector->X * 82 + 52;
	aDstRect.y = YOffsetStageSelect + selector->Y * 14 - 6;
	aDstRect.w = selector->Image->w;
	aDstRect.h = selector->Image->h;
	SDL_BlitSurface(selector->Image,NULL,Screen,&aDstRect);
}

void CStageSelectSelector_MoveDown(CStageSelectSelector* selector)
{
	if (selector->Y < 11)
	{
		selector->Y++;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void CStageSelectSelector_MoveLeft(CStageSelectSelector* selector)
{
	if (selector->X > 0)
	{
		selector->X--;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void CStageSelectSelector_MoveRight(CStageSelectSelector* selector)
{
	if (selector->X < 2)
	{
		selector->X++;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void CStageSelectSelector_MoveUp(CStageSelectSelector* selector)
{
	if ( selector->Y > 0)
	{
		selector->Y--;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}

}

int CStageSelectSelector_GetSelection(CStageSelectSelector* selector)
{
	return  selector->X + selector->Y * 3;
}

void CStageSelectSelector_destroy(CStageSelectSelector* selector)
{
	SDL_FreeSurface(selector->Image);
	free (selector);
}
