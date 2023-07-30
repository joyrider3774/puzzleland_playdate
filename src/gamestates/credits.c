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
	char *Tekst = "Puzzle Land is programmed by\nWillems Davy. Graphics are made\nusing gimp. A Big thanks goes out\nto Yann R. Fernandez for creating\nsome of the graphics.\n\nPuzzle Land is a remake of\nDaedalian opus for gameboy by\nVic Tokai Inc. 1990";

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
	pd->graphics->pushContext(NULL);
	pd->graphics->setFont(NULL);
	pd->graphics->drawText("CREDITS", strlen("CREDITS"), kASCIIEncoding, WINDOW_WIDTH / 2 - 32, 20);
	pd->graphics->drawText(Tekst, CreditsNrOfChars,kASCIIEncoding, 30, 40);
	pd->graphics->popContext();

	if (GameState != GSCredits)
		CreditsDeInit();
}
