#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "../commonvars.h"
#include "chand.h"


CHand* CHand_Create()
{
	CHand* Result = (CHand *) malloc(sizeof(CHand));
	Result->Image = IMG_Load("./graphics/hand.png");
	Result->Hidden = false;
	Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CHand_Draw(CHand* Hand)
{
	SDL_Rect aDstRect;
	if (!Hand->Hidden)
	{
		aDstRect.x = MinPlayAreaX + Hand->X * BlockWidth;
		aDstRect.y = MinPlayAreaY + Hand->Y * BlockHeight;
		aDstRect.w = Hand->Image->w;
		aDstRect.h = Hand->Image->h;
		SDL_BlitSurface(Hand->Image,NULL,Screen,&aDstRect);
	}
}

void CHand_Move(CHand* Hand)
{
	if (!Hand->Hidden)
	{
		Uint8* keystate = SDL_GetKeyState(NULL);
		if (keystate[SDLK_UP])
		{
			if (Hand->Y - 1 >= 0)
				Hand->Y = Hand->Y - 1;
		}
		else if (keystate[SDLK_DOWN])
		{
			if (Hand->Y + 1 < Rows)
				Hand->Y = Hand->Y + 1;
		}
		
		if (keystate[SDLK_LEFT])
		{
			if (Hand->X - 1 >= 0)
				Hand->X = Hand->X - 1;
		}
		else if (keystate[SDLK_RIGHT])
		{
			if (Hand->X + 1 < Cols)
				Hand->X = Hand->X + 1;
		}
	}
}

void CHand_SetPosition(CHand* Hand, const int XIn,const int YIn)
{
	Hand->X = XIn;
	Hand->Y = YIn;
}

int CHand_GetPlayFieldX(CHand* Hand)
{
	return Hand->X;
}

int CHand_GetPlayFieldY(CHand* Hand)
{
	return Hand->Y;
}

void CHand_Hide(CHand* Hand)
{
	Hand->Hidden = true;
}

void CHand_Show(CHand* Hand)
{
	Hand->Hidden = false;
}

void CHand_Destroy(CHand* Hand)
{
	SDL_FreeSurface(Hand->Image);
	free(Hand);
}
