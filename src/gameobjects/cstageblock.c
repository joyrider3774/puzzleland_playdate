#include <SDL.h>
#include <SDL_image.h>
#include "../commonvars.h"
#include "cstageblock.h"


CStageBlock* CStageBlock_Create()
{
	CStageBlock* Result = (CStageBlock *) malloc(sizeof(CStageBlock));
	Result->Image=NULL;
 	return Result;
}

void CStageBlock_Load(CStageBlock* stageBlock, const int BlockNr)
{
	char ChrFileName[FILENAME_MAX];
	sprintf(ChrFileName,"./graphics/stageblock%d.png",BlockNr);
	stageBlock->Image = IMG_Load(ChrFileName);
	stageBlock->Hidden = false;
	stageBlock->Yi = 3;
	stageBlock->X = 160 - stageBlock->Image->w / 2;
	stageBlock->Y = -stageBlock->Image->h;
	stageBlock->Width = stageBlock->Image->w;
	stageBlock->Height = stageBlock->Image->h;
}

void CStageBlock_Draw(CStageBlock* stageBlock)
{
	SDL_Rect aDstRect;
	if (!stageBlock->Hidden)
	{
		aDstRect.x = stageBlock->X;
		aDstRect.y = stageBlock->Y;
		aDstRect.w = stageBlock->Width;
		aDstRect.h = stageBlock->Height;
		SDL_BlitSurface(stageBlock->Image,NULL,Screen,&aDstRect);
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
		SDL_FreeSurface(stageBlock->Image);
	}
	free(stageBlock);
}
