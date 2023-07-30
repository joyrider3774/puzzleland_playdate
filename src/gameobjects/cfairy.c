#include <stdbool.h>
#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "cfairy.h"


CFairy* CFairy_Create(const int XIn, const int YIn,const int AnimDelayIn)
{
	CFairy* Result = pd->system->realloc(NULL, sizeof(CFairy));
	Result->Image = loadImageAtPath("graphics/ryf-fairy");
	Result->X = XIn;
	Result->Y = YIn;
	Result->Width = 18;
	Result->Height = 22;
	Result->AnimPhase = 0;
	Result->Delay = 0;
	Result->Hidden = false;
	Result->AnimDelay = AnimDelayIn;
	return Result;
}

void CFairy_Draw(CFairy* Fairy)
{
	//SDL_Rect SrcRect,DstRect;
	if (!Fairy->Hidden)
	{
		/*SrcRect.x = Fairy->AnimPhase * Fairy->Width;
		SrcRect.y = 0;
		SrcRect.w = Fairy->Width;
		SrcRect.h = Fairy->Height;
		DstRect.x = Fairy->X;
		DstRect.y = Fairy->Y;
		DstRect.w = Fairy->Width;
		DstRect.h = Fairy->Height;
		SDL_BlitSurface(Fairy->Image,&SrcRect,Screen,&DstRect);
		*/
		DrawBitmapSrcRec(Fairy->Image, Fairy->X, Fairy->Y, Fairy->AnimPhase * Fairy->Width, 0, Fairy->Width, Fairy->Height, kBitmapUnflipped);
		Fairy->Delay++;
		if (Fairy->Delay >= Fairy->AnimDelay)
		{
			Fairy->AnimPhase++;
			Fairy->Delay = 0;
			if (Fairy->AnimPhase == 2)
				Fairy->AnimPhase = 0;
		}
	}
}

int CFairy_GetX(CFairy* Fairy)
{
	return Fairy->X;
}

void CFairy_Destroy(CFairy* Fairy)
{
	pd->graphics->freeBitmap(Fairy->Image);
	pd->system->realloc(Fairy, 0);
}
