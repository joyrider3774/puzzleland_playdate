#include <pd_api.h>
#include <stdbool.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../gameobjects/cstageselectselector.h"
#include "../commonvars.h"
#include "stageselect.h"


CStageSelectSelector *StageSelectSelector;

void StageSelectInit()
{
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

	/*SDL_Rect aDstRect;
	SDL_Color Color1 = {0,0,0,0};
	SDL_BlitSurface(Background,NULL,Screen,NULL);
	Text = TTF_RenderText_Solid(font,"ROOM SELECT",Color1);
	aDstRect.x = Screen->w / 2 - Text->w / 2;
	aDstRect.y = 20;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	pd->graphics->freeBitmap(Text);*/

	pd->graphics->clear(kColorWhite);
	pd->graphics->setBackgroundColor(kColorWhite);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
	int textw = pd->graphics->getTextWidth(Mini, "ROOM SELECT", strlen("ROOM SELECT"), kASCIIEncoding, 0);
	pd->graphics->drawText("ROOM SELECT", strlen("ROOM SELECT"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - (textw >> 1), 20);
	
	int Teller;
	char* ChrRoom;
	for (Teller=0;Teller< 36;Teller++)
	{
		pd->system->formatString(&ChrRoom,"Room %d",Teller+1);

		/*Text = TTF_RenderText_Solid(font,ChrRoom,Color1);
		aDstRect.x = XOffsetStageSelect + (Teller % 3) * 82;
		aDstRect.y = YOffsetStageSelect + (Teller / 3) * 14;
		aDstRect.w = Text->w;
		aDstRect.h = Text->h;
		SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
		pd->graphics->freeBitmap(Text);*/
		pd->graphics->drawText(ChrRoom, strlen(ChrRoom), kASCIIEncoding, XOffsetStageSelect + (Teller % 3) * 82, YOffsetStageSelect + (Teller / 3) * 14);
	}
	CStageSelectSelector_Draw(StageSelectSelector);

	if(GameState != GSStageSelect)
		StageSelectDeInit();
}
