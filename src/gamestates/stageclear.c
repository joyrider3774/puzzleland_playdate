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
	
	pd->graphics->clear(kColorBlack);
	pd->graphics->setBackgroundColor(kColorBlack);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	pd->graphics->drawBitmap(RoomBackground, 0, 0, kBitmapUnflipped);
	DrawPanel();
	DrawPlayField();
	if (KaderVisible)
	{
		int w;
		pd->graphics->getBitmapData(StageClearKader, &w, NULL, NULL, NULL, NULL);
		pd->graphics->drawBitmap(StageClearKader, (WINDOW_WIDTH - w)>>1, YOffsetGame + 75, kBitmapUnflipped);
	}

	if(GameState != GSStageClear)
		StageClearDeInit();
}
