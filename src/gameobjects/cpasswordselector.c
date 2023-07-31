#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "../sound.h"
#include "cpasswordselector.h"


CPasswordSelector* CPasswordSelector_Create()
{
	CPasswordSelector* Result = pd->system->realloc(NULL, sizeof(CPasswordSelector));
	Result->Image = loadImageAtPath("graphics/select");
	Result->X = 0;
	Result->Y = 0;
	return Result;
}

void CPasswordSelector_Draw(CPasswordSelector* Selector)
{
	int h;
	pd->graphics->getBitmapData(Selector->Image, NULL, &h, NULL, NULL, NULL);
	pd->graphics->drawBitmap(Selector->Image, XOffsetPassword + 3 + Selector->X * 35, YOffsetPassword + Selector->Y * 35 - (h >> 2), kBitmapUnflipped);
}

void CPasswordSelector_MoveDown(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows - 2)
	{
		Selector->Y = Selector->Y + 1;
		playMenuSound();
	}
	else
		if ((Selector->Y == LetterRows -2) && (Selector->X < LetterCols -2))
		{
			Selector->Y = Selector->Y + 1;
			playMenuSound();
		}
}

void CPasswordSelector_MoveLeft(CPasswordSelector* Selector)
{
	if (Selector->X > 0)
	{
		Selector->X = Selector->X -1;
		playMenuSound();
	}
}

void CPasswordSelector_MoveRight(CPasswordSelector* Selector)
{
	if (Selector->Y < LetterRows -1)
		if (Selector->X < LetterCols -1)
		{
			Selector->X = Selector->X + 1;
			playMenuSound();
		}

	if (Selector->Y == LetterRows - 1)
		if (Selector->X < LetterCols -3)
		{
			Selector->X = Selector->X + 1;
			playMenuSound();
		}
}

void CPasswordSelector_MoveUp(CPasswordSelector* Selector)
{
	if (Selector->Y > 0)
	{
		Selector->Y = Selector->Y - 1;
		playMenuSound();
	}
}

int CPasswordSelector_GetX(CPasswordSelector* Selector)
{
	return Selector->X;
}

int CPasswordSelector_GetY(CPasswordSelector* Selector)
{
	return Selector->Y;
}

void CPasswordSelector_Destroy(CPasswordSelector* Selector)
{
	pd->graphics->freeBitmap(Selector->Image);
	pd->system->realloc(Selector, 0);
}
