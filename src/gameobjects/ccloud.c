#include <pd_api.h>
#include "../commonvars.h"
#include "../pd_helperfuncs.h"
#include "ccloud.h"

CCloud* CCloud_Create(const int XIn,const int YIn,float XiIn,CloudStyles Style)
{
	CCloud* Result = pd->system->realloc(NULL, sizeof(CCloud));
	if (Style == Big)
	{
		Result->Image = loadImageAtPath("graphics/ryf-cloud");
		Result->Width = 60;
		Result->Height = 28;
	}
	else
	{
		Result->Image = loadImageAtPath("graphics/ryf-smallcloud");
		Result->Width=30;
		Result->Height=14;
	 }
	Result->X = XIn;
	Result->Y = YIn;
	Result->Xi = XiIn;
	return Result;
}

void CCloud_Draw(CCloud* Cloud)
{
	//SDL_Rect SrcRect,DstRect;
	if ((Cloud->X < 0) && (Cloud->X >= -Cloud->Width))
	{
		/*SrcRect.x = abs((int)Cloud->X);
		SrcRect.y = 0;
		SrcRect.w = abs((int)Cloud->X) + Cloud->Width;
		SrcRect.h = Cloud->Height;
		DstRect.x = (int)Cloud->X;
		DstRect.y = Cloud->Y;
		DstRect.w = (int)Cloud->X + Cloud->Width;
		DstRect.h = Cloud->Height;
		SDL_BlitSurface(Cloud->Image,&SrcRect,Screen,&DstRect);
		*/
		DrawBitmapSrcRec(Cloud->Image, (int)Cloud->X, Cloud->Y, abs((int)Cloud->X), 0, abs((int)Cloud->X) + Cloud->Width, Cloud->Height, kBitmapUnflipped);
	}
	else
		if((Cloud->X >=0) && (Cloud->X <= WINDOW_WIDTH - 1 - Cloud->Width))
		{
			/*SrcRect.x = 0;
			SrcRect.y = 0;
			SrcRect.w = Cloud->Width;
			SrcRect.h = Cloud->Height;
			DstRect.x = (int)Cloud->X;
			DstRect.y = Cloud->Y;
			DstRect.w = Cloud->Width;
			DstRect.h = Cloud->Height;
			SDL_BlitSurface(Cloud->Image,&SrcRect,Screen,&DstRect);*/
			DrawBitmapSrcRec(Cloud->Image, (int)Cloud->X, Cloud->Y, 0, 0, Cloud->Width, Cloud->Height, kBitmapUnflipped);
		}
		else
			if((Cloud->X > WINDOW_WIDTH - 1 - Cloud->Width) && (Cloud->X < WINDOW_WIDTH))
			{
				/*SrcRect.x = 0;
				SrcRect.y =0;
				SrcRect.w = WINDOW_WIDTH -1 - (int)Cloud->X;
				SrcRect.h = Cloud->Height;
				DstRect.x = (int)Cloud->X;
				DstRect.y = Cloud->Y;
				DstRect.w = WINDOW_WIDTH - 1 -(int)Cloud->X;
				DstRect.h = Cloud->Height;
				SDL_BlitSurface(Cloud->Image,&SrcRect,Screen,&DstRect);*/
				DrawBitmapSrcRec(Cloud->Image, (int)Cloud->X, Cloud->Y, 0, 0, WINDOW_WIDTH - 1 - (int)Cloud->X, Cloud->Height, kBitmapUnflipped);
			}
}

void CCloud_Move(CCloud* Cloud)
{
	if ((Cloud->X > -Cloud->Width) && (Cloud->X < WINDOW_WIDTH))
		Cloud->X = Cloud->X + Cloud->Xi;
	else
		if (Cloud->X <= -Cloud->Width)
			Cloud->X = 319;
		else
			Cloud->X = -Cloud->Width + 1;
}


void CCloud_Destroy(CCloud* Cloud)
{
	pd->graphics->freeBitmap(Cloud->Image);
	pd->system->realloc(Cloud, 0);
}
