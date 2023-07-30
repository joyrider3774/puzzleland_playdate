#include <pd_api.h>
#include "../sound.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "stageclear.h"


bool KaderVisible;

void StageClearInit()
{
	KaderVisible = true;
}

void StageClearDeInit()
{

}

void StageClear()
{
	if(GameState == GSStageClearInit)
	{
		StageClearInit();
		GameState -= GSInitDiff;
	}
				/*case SDLK_ESCAPE :
					Mix_HaltChannel(0);
					Mix_HaltChannel(1);
					Mix_HaltMusic();
					GameState = GSTitleScreenInit;
					break;*/
	
	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
		GameState = GSOldManSpeakingInit;
	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
		KaderVisible = !KaderVisible;
	
	/*SDL_Rect aDstRect;
	aDstRect.x = XOffsetGame-4;
	aDstRect.y = YOffsetGame + 75;
	aDstRect.w = StageClearKader->w;
	aDstRect.h = StageClearKader->h;
	SDL_BlitSurface(RoomBackground,NULL,Screen,NULL);
	*/
	pd->graphics->drawBitmap(RoomBackground, 0, 0, kBitmapUnflipped);
	DrawPanel();
	DrawPlayField();
	if (KaderVisible)
		pd->graphics->drawBitmap(StageClearKader, XOffsetGame - 4, YOffsetGame + 75, kBitmapUnflipped);
	//	SDL_BlitSurface(StageClearKader,NULL,Screen,&aDstRect);

	if(GameState != GSStageClear)
		StageClearDeInit();
}
