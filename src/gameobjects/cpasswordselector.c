#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../commonvars.h"
#include "cpasswordselector.h"


CPasswordSelector* CPasswordSelector_Create()
{
	CPasswordSelector* Result = (CPasswordSelector *) malloc(sizeof(CPasswordSelector));
	Result->Image = IMG_Load("./graphics/select.png");
	Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CPasswordSelector_Draw(CPasswordSelector* Selector)
{
	SDL_Rect aDstRect;
	aDstRect.x = XOffsetPassword + Selector->X * 35;
	aDstRect.y = YOffsetPassword + Selector->Y * 35 - (Selector->Image->h >> 2);
	aDstRect.w = Selector->Image->w;
	aDstRect.h = Selector->Image->h;
	SDL_BlitSurface(Selector->Image,NULL,Screen,&aDstRect);
}

void CPasswordSelector_MoveDown(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows - 2)
	{
		Selector->Y = Selector->Y + 1;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
	else
		if ((Selector->Y == LetterRows -2) && (Selector->X < LetterCols -2))
		{
			Selector->Y = Selector->Y + 1;
			if (GlobalSoundEnabled && SoundEnabled)
				Mix_PlayChannel(-1,Sounds[SND_Menu],0);
		}
}

void CPasswordSelector_MoveLeft(CPasswordSelector* Selector)
{
	if (Selector->X > 0)
	{
		Selector->X = Selector->X -1;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

void CPasswordSelector_MoveRight(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows -1)
		if (Selector->X < LetterCols -1)
		{
			Selector->X = Selector->X + 1;
			if (GlobalSoundEnabled && SoundEnabled)
				Mix_PlayChannel(-1,Sounds[SND_Menu],0);
		}

	if (Selector->Y == LetterRows - 1)
		if (Selector->X < LetterCols -3)
		{
			Selector->X = Selector->X + 1;
			if (GlobalSoundEnabled && SoundEnabled)
				Mix_PlayChannel(-1,Sounds[SND_Menu],0);
		}
}

void CPasswordSelector_MoveUp(CPasswordSelector* Selector)
{
	if (Selector->Y > 0)
	{
		Selector->Y = Selector->Y - 1;
		if (GlobalSoundEnabled && SoundEnabled)
			Mix_PlayChannel(-1,Sounds[SND_Menu],0);
	}
}

int CPasswordSelector_GetX(CPasswordSelector* Selector)
{
	return Selector->X;
}

int CPasswordSelector_GetY(CPasswordSelector* Selector)
{
	return Selector->Y;
}

void CPasswordSelector_Destroy(CPasswordSelector* Selector)
{
	SDL_FreeSurface(Selector->Image);
	free(Selector);
}
