#ifndef CSTAGESELECTSELECTOR_H
#define CSTAGESELECTSELECTOR_H

#include <pd_api.h>

typedef struct CStageSelectSelector CStageSelectSelector;
struct CStageSelectSelector
{
	int X,Y;
 	LCDBitmap* Image;
};

CStageSelectSelector* CStageSelectSelector_Create();
void CStageSelectSelector_Draw(CStageSelectSelector* selector);
void CStageSelectSelector_MoveDown(CStageSelectSelector* selector);
void CStageSelectSelector_MoveLeft(CStageSelectSelector* selector);
void CStageSelectSelector_MoveRight(CStageSelectSelector* selector);
void CStageSelectSelector_MoveUp(CStageSelectSelector* selector);
int CStageSelectSelector_GetSelection(CStageSelectSelector* selector);
void CStageSelectSelector_destroy(CStageSelectSelector* selector);

#endif