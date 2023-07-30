#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../gameobjects/coptionsselector.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"
#include "options.h"

COptionsSelector* Selector;

void OptionsInit()
{
	Selector = COptionsSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void OptionsDeInit()
{
	pd->graphics->freeBitmap(Background);
	COptionsSelector_Destroy(Selector);
	SaveSettings();
}

void Options()
{
	if(GameState == GSOptionsInit)
	{
		OptionsInit();
		GameState -= GSInitDiff;
	}

	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
	{
		GameState = GSTitleScreenInit;
	}

	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		if (COptionsSelector_GetSelection(Selector) == 1)
			setSoundOn(!isSoundOn());
	
		if (COptionsSelector_GetSelection(Selector) == 2)
			setMusicOn(!isMusicOn());

		playMenuSelectSound();
	}
	
	if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
		COptionsSelector_MoveUp(Selector);
	
	if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
		COptionsSelector_MoveDown(Selector);

	/*SDL_BlitSurface(Background,NULL,Screen,NULL);
	TTF_SetFontStyle(font,TTF_STYLE_UNDERLINE);
	SDL_Color Color1 = {0,0,0,0};
	WriteText(Screen,font,"OPTIONS",7,Screen->w / 2 - 25,20,0,Color1);
	TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
	char Msg[20];
	if(SoundEnabled)
		strcpy(Msg,"SOUND: ON");
	else
		strcpy(Msg,"SOUND: OFF");
	WriteText(Screen,font,Msg,strlen(Msg),Screen->w / 2 -35,40,0,Color1);
	if (MusicEnabled)
		strcpy(Msg,"MUSIC: ON");
	else
		strcpy(Msg,"MUSIC: OFF");
	WriteText(Screen,font,Msg,strlen(Msg),Screen->w / 2 -35,60,0,Color1);*/

	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
	if (isSoundOn())
		pd->graphics->drawText("SOUND: ON", strlen("SOUND: ON"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 35, 40);
	else
		pd->graphics->drawText("SOUND: OFF", strlen("SOUND: OFF"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 35, 40);
	
	if (isMusicOn())
		pd->graphics->drawText("MUSIC: ON", strlen("MUSIC: ON"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 35, 60);
	else
		pd->graphics->drawText("MUSIC: OFF", strlen("MUSIC: OFF"), kASCIIEncoding, (WINDOW_WIDTH >> 1) - 35, 60);
	

	COptionsSelector_Draw(Selector);

	if(GameState != GSOptions)
		OptionsDeInit();
}
