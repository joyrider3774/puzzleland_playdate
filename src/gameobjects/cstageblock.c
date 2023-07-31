#include <stdio.h>
#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "cstageblock.h"


CStageBlock* CStageBlock_Create()
{
	CStageBlock* Result = pd->system->realloc(NULL, sizeof(CStageBlock));
	Result->Image=NULL;
 	return Result;
}

void CStageBlock_Load(CStageBlock* stageBlock, const int BlockNr)
{
	char* ChrFileName;
	pd->system->formatString(&ChrFileName, "./graphics/stageblock%d",BlockNr);
	stageBlock->Image = loadImageAtPath(ChrFileName);
	pd->system->realloc(ChrFileName, 0);
	int w, h;
	pd->graphics->getBitmapData(stageBlock->Image, &w, &h, NULL, NULL, NULL);
	stageBlock->Hidden = false;
	stageBlock->Yi = 3;
	stageBlock->X = 160 - w / 2;
	stageBlock->Y = -h;
	stageBlock->Width = w;
	stageBlock->Height = h;
}

void CStageBlock_Draw(CStageBlock* stageBlock)
{
	if (!stageBlock->Hidden)
	{
		pd->graphics->drawBitmap(stageBlock->Image, stageBlock->X, stageBlock->Y, kBitmapUnflipped);
	}
}

void CStageBlock_Move(CStageBlock* stageBlock)
{
	if (!stageBlock->Hidden)
		stageBlock->Y = stageBlock->Y + stageBlock->Yi;
}

int CStageBlock_GetY(CStageBlock* stageBlock)
{
	return stageBlock->Y;
}

int CStageBlock_GetHeight(CStageBlock* stageBlock)
{
	return stageBlock->Height;
}

void CStageBlock_destroy(CStageBlock* stageBlock)
{
	if (stageBlock->Image != NULL)
	{
		pd->graphics->freeBitmap(stageBlock->Image);
	}
	pd->system->realloc(stageBlock, 0);
}
