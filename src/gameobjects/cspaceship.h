#ifndef CSPACESHIP_H
#define CSPACESHIP_H

#include <pd_api.h>

typedef struct CSpaceShip CSpaceShip;
struct CSpaceShip
{
 	int X,Y;
 	LCDBitmap* Image;
};

void CSpaceShip_destroy(CSpaceShip* spaceShip);
int CSpaceShip_GetX(CSpaceShip* spaceShip);
void CSpaceShip_Move(CSpaceShip* spaceShip);
void CSpaceShip_Draw(CSpaceShip* spaceShip);
CSpaceShip* CSpaceShip_Create();

#endif