#ifndef CCLOUD_H
#define CCLOUD_H

#include <pd_api.h>

typedef enum {Big,Small} CloudStyles;

typedef struct CCloud CCloud;
struct CCloud
{
 	float X,Xi;
 	int Y,Width,Height;
 	LCDBitmap* Image;
} ;

void CCloud_Destroy(CCloud* Cloud);
void CCloud_Move(CCloud* Cloud);
void CCloud_Draw(CCloud* Cloud);
CCloud* CCloud_Create(const int XIn,const int YIn,float XiIn,CloudStyles Style);

#endif