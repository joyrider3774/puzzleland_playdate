#include <stdio.h>
#include <stdbool.h>
#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "chand.h"

CHand* CHand_Create()
{
	CHand* Result = pd->system->realloc(NULL, sizeof(CHand));
	Result->Image = loadImageAtPath("graphics/hand");
	Result->Hidden = false;
	Result->X = 0;
	Result->Y = 0;
	Result->MoveCoolDown = 0;
	return Result;
}

void CHand_Draw(CHand* Hand)
{
	if (!Hand->Hidden)
	{
		pd->graphics->drawBitmap(Hand->Image, MinPlayAreaX + Hand->X * BlockWidth, MinPlayAreaY + Hand->Y * BlockHeight, kBitmapUnflipped);
	}
}

void CHand_Move(CHand* Hand)
{
	if (Hand->MoveCoolDown > 0)
		Hand->MoveCoolDown--;
	if ((!Hand->Hidden) && (Hand->MoveCoolDown == 0))
	{
		if (currButtons & kButtonUp)
		{
			if (Hand->Y - 1 >= 0)
			{
				Hand->Y = Hand->Y - 1;
				Hand->MoveCoolDown = 3;
			}
		}
		else if (currButtons & kButtonDown)
		{
			if (Hand->Y + 1 < Rows)
			{
				Hand->Y = Hand->Y + 1;
				Hand->MoveCoolDown = 3;
			}
		}
		
		if (currButtons & kButtonLeft)
		{
			if (Hand->X - 1 >= 0)
			{
				Hand->X = Hand->X - 1;
				Hand->MoveCoolDown = 3;
			}
		}
		else if (currButtons & kButtonRight)
		{
			if (Hand->X + 1 < Cols)
			{
				Hand->X = Hand->X + 1;
				Hand->MoveCoolDown = 3;
			}
		}
	}
}

void CHand_SetPosition(CHand* Hand, const int XIn,const int YIn)
{
	Hand->X = XIn;
	Hand->Y = YIn;
}

int CHand_GetPlayFieldX(CHand* Hand)
{
	return Hand->X;
}

int CHand_GetPlayFieldY(CHand* Hand)
{
	return Hand->Y;
}

void CHand_Hide(CHand* Hand)
{
	Hand->Hidden = true;
}

void CHand_Show(CHand* Hand)
{
	Hand->Hidden = false;
}

void CHand_Destroy(CHand* Hand)
{
	pd->graphics->freeBitmap(Hand->Image);
	pd->system->realloc(Hand, 0);
}
