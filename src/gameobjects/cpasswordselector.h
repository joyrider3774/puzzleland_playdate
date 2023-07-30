#ifndef CPASSWORDSELECTOR_H
#define CPASSWORDSELECTOR_H

#include <SDL.h>

typedef struct CPasswordSelector CPasswordSelector;
struct CPasswordSelector
{
 	SDL_Surface* Image;
 	int X,Y;
} ;

void CPasswordSelector_Destroy(CPasswordSelector* Selector);
int CPasswordSelector_GetY(CPasswordSelector* Selector);
int CPasswordSelector_GetX(CPasswordSelector* Selector);
void CPasswordSelector_MoveUp(CPasswordSelector* Selector);
void CPasswordSelector_MoveRight(CPasswordSelector* Selector);
void CPasswordSelector_MoveLeft(CPasswordSelector* Selector);
void CPasswordSelector_MoveDown(CPasswordSelector* Selector);
void CPasswordSelector_Draw(CPasswordSelector* Selector);
CPasswordSelector* CPasswordSelector_Create();

#endif