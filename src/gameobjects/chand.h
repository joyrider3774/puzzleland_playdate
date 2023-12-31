#ifndef CHAND_H
#define CHAND_H

#include <pd_api.h>
#include <stdbool.h>

typedef struct CHand CHand;
struct CHand
{
 	int X,Y,MoveCoolDown;
 	bool Hidden;
 	LCDBitmap* Image;
};

void CHand_Destroy(CHand* Hand);
void CHand_Show(CHand* Hand);
void CHand_Hide(CHand* Hand);
int CHand_GetPlayFieldY(CHand* Hand);
int CHand_GetPlayFieldX(CHand* Hand);
void CHand_SetPosition(CHand* Hand, const int XIn,const int YIn);
void CHand_Move(CHand* Hand);
void CHand_Draw(CHand* Hand);
CHand* CHand_Create();

#endif