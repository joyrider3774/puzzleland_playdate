#ifndef CFAIRY_H
#define CFAIRY_H

#include <pd_api.h>
#include <stdbool.h>

typedef struct CFairy CFairy;
struct CFairy
{
  	bool Hidden;
 	int X,Y,Width,Height,Delay,AnimPhase,AnimDelay;
 	LCDBitmap* Image;
} ;

void CFairy_Destroy(CFairy* Fairy);
int CFairy_GetX(CFairy* Fairy);
void CFairy_Draw(CFairy* Fairy);
CFairy* CFairy_Create(const int XIn, const int YIn,const int AnimDelayIn);

#endif