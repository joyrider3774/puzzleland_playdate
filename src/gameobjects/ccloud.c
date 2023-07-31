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
	pd->graphics->drawBitmap(Cloud->Image, (int)Cloud->X, Cloud->Y, kBitmapUnflipped);
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
