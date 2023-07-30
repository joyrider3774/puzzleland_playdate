#ifndef COPTIONSSELECTOR_H
#define COPTIONSSELECTOR_H

#include <pd_api.h>

typedef struct COptionsSelector COptionsSelector;
struct COptionsSelector
{
 	LCDBitmap* Image;
 	int Selection;
};

void COptionsSelector_Destroy(COptionsSelector* Selector);
void COptionsSelector_MoveUp(COptionsSelector* Selector);
void COptionsSelector_MoveDown(COptionsSelector* Selector);
int COptionsSelector_GetSelection(COptionsSelector* Selector);
void COptionsSelector_Draw(COptionsSelector* Selector);
COptionsSelector* COptionsSelector_Create();

#endif