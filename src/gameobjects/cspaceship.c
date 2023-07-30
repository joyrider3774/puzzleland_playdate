#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "cspaceship.h"


CSpaceShip* CSpaceShip_Create()
{
	CSpaceShip* Result = pd->system->realloc(NULL, sizeof(CSpaceShip));
	Result->Image = loadImageAtPath("graphics/spaceship");
	Result->X=-53;
	Result->Y= 22;
	return Result;
}

void CSpaceShip_Draw(CSpaceShip* spaceShip)
{
	/*SDL_Rect aDstRect;
	aDstRect.x = spaceShip->X;
	aDstRect.y = spaceShip->Y;
	aDstRect.w = spaceShip->Image->w;
	aDstRect.h = spaceShip->Image->h;
	SDL_BlitSurface(spaceShip->Image,NULL,Screen,&aDstRect);*/
	pd->graphics->drawBitmap(spaceShip->Image, spaceShip->X, spaceShip->Y, kBitmapUnflipped);
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
	pd->graphics->freeBitmap(spaceShip->Image);
	pd->system->realloc(spaceShip, 0);
}
