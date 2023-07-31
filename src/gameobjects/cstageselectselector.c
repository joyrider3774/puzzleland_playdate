#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../commonvars.h"
#include "cstageselectselector.h"


CStageSelectSelector* CStageSelectSelector_Create()
{
	CStageSelectSelector* Result = pd->system->realloc(NULL, sizeof(CStageSelectSelector));
	Result->Image= loadImageAtPath("graphics/select");
    Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CStageSelectSelector_Draw(CStageSelectSelector* selector)
{
	pd->graphics->drawBitmap(selector->Image, XOffsetStageSelect + selector->X * 82 + 52, YOffsetStageSelect + selector->Y * 15 - 3, kBitmapUnflipped);
}

void CStageSelectSelector_MoveDown(CStageSelectSelector* selector)
{
	if (selector->Y < 11)
	{
		selector->Y++;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveLeft(CStageSelectSelector* selector)
{
	if (selector->X > 0)
	{
		selector->X--;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveRight(CStageSelectSelector* selector)
{
	if (selector->X < 2)
	{
		selector->X++;
		playMenuSound();
	}
}

void CStageSelectSelector_MoveUp(CStageSelectSelector* selector)
{
	if ( selector->Y > 0)
	{
		selector->Y--;
		playMenuSound();
	}
}

int CStageSelectSelector_GetSelection(CStageSelectSelector* selector)
{
	return  selector->X + selector->Y * 3;
}

void CStageSelectSelector_destroy(CStageSelectSelector* selector)
{
	pd->graphics->freeBitmap(selector->Image);
	pd->system->realloc(selector, 0);
}
