#include "pd_api.h"
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "credits.h"

size_t CreditsNrOfChars;

void CreditsInit()
{
	CreditsNrOfChars = 0;
	Background = loadImageAtPath("graphics/paper");
}

void CreditsDeInit()
{
	pd->graphics->freeBitmap(Background);
}

void Credits()
{
	char *Tekst = "Puzzle Land is programmed by\nWillems Davy. Graphics are made\nusing Paint Shop Pro 7. A Big thanks\ngoes out to Yann R. Fernandez for\ncreating some of the graphics.\nPuzzle Land is a remake of\nDaedalian opus for gameboy by\nVic Tokai Inc. 1990\n\nWillems Soft 2006";

	if(GameState == GSCreditsInit)
	{
		CreditsInit();
		GameState -= GSInitDiff;
	}
	
	if (((currButtons & kButtonA) && (!(prevButtons & kButtonA))) ||
		((currButtons & kButtonB) && (!(prevButtons & kButtonB))))
		GameState = GSTitleScreenInit;

	if (CreditsNrOfChars < strlen(Tekst))
		CreditsNrOfChars++;

	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
	pd->graphics->drawText("CREDITS", strlen("CREDITS"), kASCIIEncoding, WINDOW_WIDTH / 2 - 32, 20);
	pd->graphics->drawText(Tekst, CreditsNrOfChars,kASCIIEncoding, 30, 40);
	//SDL_BlitSurface(Background,NULL,Screen,NULL);
	//TTF_SetFontStyle(font,TTF_STYLE_UNDERLINE);
	//SDL_Color Color1 = {0,0,0,0};
	/*WriteText(Screen,font,"CREDITS",7,Screen-> w / 2 - 32,20,0,Color1);
	TTF_SetFontStyle(font,TTF_STYLE_NORMAL);*/
	//WriteText(Screen,font,Tekst,CreditsNrOfChars,30,40,0,Color1);
	
	if (GameState != GSCredits)
		CreditsDeInit();
}
