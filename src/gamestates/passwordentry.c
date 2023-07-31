#include <pd_api.h>
#include "../sound.h"
#include "../pd_helperfuncs.h"
#include "../gameobjects/cpasswordselector.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "passwordentry.h"


int CharNr;
char Password[5];
CPasswordSelector* PasswordSelector;

void PasswordEntryInit()
{
	CreateOtherMenuItems();
	PasswordEntryCoolDown = 0;
	CharNr = 0;
	Password[0] = ' ';
	Password[1] = ' ';
	Password[2] = ' ';
	Password[3] = ' ';
	Password[4] = '\0';
	PasswordSelector = CPasswordSelector_Create();
	Background = loadImageAtPath("graphics/paper");
}

void PassWordEntryDeInit()
{
	pd->graphics->freeBitmap(Background);
	CPasswordSelector_Destroy(PasswordSelector);
}

void PasswordEntry()
{
	
	if(GameState == GSPasswordEntryInit)
	{
		PasswordEntryInit();
		GameState -= GSInitDiff;
	}
	
	if (Password[3] != ' ')
	{
		if (PasswordEntryCoolDown > 0)
			PasswordEntryCoolDown--;
		if (PasswordEntryCoolDown == 0)
		{
			if (GetLevel(Password) == -1)
			{
				Password[0] = ' ';
				Password[1] = ' ';
				Password[2] = ' ';
				Password[3] = ' ';
				playErrorSound();
			}
			else
				if (GetLevel(Password) == 0)
				{
					GameState = GSStageSelectInit;
				}
				else
				{
					Level = GetLevel(Password);
					GameState = GSOldManSpeakingInit;
				}
		}
	}

	if(GameState == GSPasswordEntry)
	{
		if (PasswordEntryCoolDown == 0)
		{
			if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
			{
				GameState = GSTitleScreenInit;
			}

			if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
			{
				Password[CharNr] = Letters[CPasswordSelector_GetY(PasswordSelector)][CPasswordSelector_GetX(PasswordSelector)];
				playMenuSelectSound();
				CharNr++;
				if (CharNr > 3)
				{
					PasswordEntryCoolDown = (int)(FRAMERATE / 2);
					CharNr = 0;
				}
			}

			if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
				CPasswordSelector_MoveUp(PasswordSelector);

			if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
				CPasswordSelector_MoveDown(PasswordSelector);

			if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
				CPasswordSelector_MoveLeft(PasswordSelector);

			if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
				CPasswordSelector_MoveRight(PasswordSelector);
		}
		pd->graphics->clear(kColorWhite);
		pd->graphics->setBackgroundColor(kColorWhite);
		pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
		pd->graphics->pushContext(NULL);
		pd->graphics->setFont(Mini2X);
		int textw = pd->graphics->getTextWidth(Mini, Password, strlen(Password), kASCIIEncoding, 0);
		pd->graphics->drawText(Password, strlen(Password), kASCIIEncoding, (WINDOW_WIDTH >> 1) - textw, 37);
		int LetterX,LetterY;
		for (LetterY = 0 ;LetterY < LetterRows;LetterY++)
			for (LetterX = 0;LetterX < LetterCols;LetterX++)
			{
				if(Letters[LetterY][LetterX] != '0')
				{
					char Letter[2] = "\0";
					Letter[0] = Letters[LetterY][LetterX];
					pd->graphics->drawText(&Letter[0], 1, kASCIIEncoding, XOffsetPassword + LetterX * 35, YOffsetPassword + LetterY * 35);
				}
			}
		pd->graphics->popContext();
		CPasswordSelector_Draw(PasswordSelector);
	}
	
	if(GameState != GSPasswordEntry)
		PassWordEntryDeInit();
}
