#include <pd_api.h>
#include <stdbool.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../gameobjects/cstageselectselector.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "stageselect.h"


CStageSelectSelector *StageSelectSelector;

void StageSelectInit()
{
	CreateOtherMenuItems();
	StageSelectSelector = CStageSelectSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void StageSelectDeInit()
{
	pd->graphics->freeBitmap(Background);
	CStageSelectSelector_destroy(StageSelectSelector);
}

void StageSelect()
{
	if(GameState == GSStageSelectInit)
	{
		StageSelectInit();
		GameState -= GSInitDiff;
	}

	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
	{
		GameState = GSPasswordEntryInit;
	}

	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		playMenuSelectSound();
		Level = CStageSelectSelector_GetSelection(StageSelectSelector);
		GameState = GSOldManSpeakingInit;
	}
	
	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		CStageSelectSelector_MoveUp(StageSelectSelector);
	
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		CStageSelectSelector_MoveDown(StageSelectSelector);
	
	if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
		CStageSelectSelector_MoveLeft(StageSelectSelector);
	
	if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
		CStageSelectSelector_MoveRight(StageSelectSelector);

	pd->graphics->clear(kColorWhite);
	pd->graphics->setBackgroundColor(kColorWhite);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
	pd->graphics->pushContext(NULL);
	pd->graphics->setFont(NULL);
	int textw = pd->graphics->getTextWidth(Mini, "ROOM SELECT", strlen("ROOM SELECT"), kASCIIEncoding, 0);
	pd->graphics->drawText("ROOM SELECT", strlen("ROOM SELECT"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - (textw >> 1) -10, 20);
	
	int Teller;
	char* ChrRoom;

	for (Teller=0;Teller< 36;Teller++)
	{
		pd->system->formatString(&ChrRoom,"Room %d",Teller+1);
		pd->graphics->drawText(ChrRoom, strlen(ChrRoom), kASCIIEncoding, XOffsetStageSelect + (Teller % 3) * 82, YOffsetStageSelect + (Teller / 3) * 15);
	}
	pd->graphics->popContext();
	CStageSelectSelector_Draw(StageSelectSelector);

	if(GameState != GSStageSelect)
		StageSelectDeInit();
}
