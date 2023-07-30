#ifndef CSTAGEBLOCK_H
#define CSTAGEBLOCK_H

#include <SDL.h>
#include <stdbool.h>

typedef struct CStageBlock CStageBlock;
struct CStageBlock
{
 	bool Hidden;
 	int X,Y,Yi,Width,Height;
 	SDL_Surface* Image;
};

void CStageBlock_destroy(CStageBlock* stageBlock);
int CStageBlock_GetHeight(CStageBlock* stageBlock);
int CStageBlock_GetY(CStageBlock* stageBlock);
void CStageBlock_Move(CStageBlock* stageBlock);
void CStageBlock_Draw(CStageBlock* stageBlock);
void CStageBlock_Load(CStageBlock* stageBlock, const int BlockNr);
CStageBlock* CStageBlock_Create();

#endif