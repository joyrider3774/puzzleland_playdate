#ifndef CSPACESHIP_H
#define CSPACESHIP_H

#include <SDL.h>

typedef struct CSpaceShip CSpaceShip;
struct CSpaceShip
{
 	int X,Y;
 	SDL_Surface* Image;
};

void CSpaceShip_destroy(CSpaceShip* spaceShip);
int CSpaceShip_GetX(CSpaceShip* spaceShip);
void CSpaceShip_Move(CSpaceShip* spaceShip);
void CSpaceShip_Draw(CSpaceShip* spaceShip);
CSpaceShip* CSpaceShip_Create();

#endif