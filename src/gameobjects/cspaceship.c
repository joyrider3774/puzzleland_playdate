#include <SDL.h>
#include <SDL_image.h>
#include "../commonvars.h"
#include "cspaceship.h"


CSpaceShip* CSpaceShip_Create()
{
	CSpaceShip* Result = (CSpaceShip *) malloc(sizeof(CSpaceShip));
	Result->Image = IMG_Load("./graphics/spaceship.png");
	Result->X=-32;
	Result->Y= 28;
	return Result;
}

void CSpaceShip_Draw(CSpaceShip* spaceShip)
{
	SDL_Rect aDstRect;
	aDstRect.x = spaceShip->X;
	aDstRect.y = spaceShip->Y;
	aDstRect.w = spaceShip->Image->w;
	aDstRect.h = spaceShip->Image->h;
	SDL_BlitSurface(spaceShip->Image,NULL,Screen,&aDstRect);
}

void CSpaceShip_Move(CSpaceShip* spaceShip)
{
	if (spaceShip->X < 352)
		spaceShip->X = spaceShip->X + 3;
}

int CSpaceShip_GetX(CSpaceShip* spaceShip)
{
	return spaceShip->X;
}

void CSpaceShip_destroy(CSpaceShip* spaceShip)
{
	SDL_FreeSurface(spaceShip->Image);
	free(spaceShip);
}
