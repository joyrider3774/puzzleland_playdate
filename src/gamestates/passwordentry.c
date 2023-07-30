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
		//SDL_Delay(250);
		if (GetLevel(Password) == -1)
		{
			Password[0] = ' ';
			Password[1] = ' ';
			Password[2] = ' ';
			Password[3] = ' ';
			playErrorSound();
		}
		else
			if(GetLevel(Password) == 0)
			{
				GameState = GSStageSelectInit;
			}
			else
			{
				Level = GetLevel(Password);
				GameState = GSOldManSpeakingInit;
				//Mix_HaltMusic();
			}
	}
	if(GameState == GSPasswordEntry)
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
				CharNr = 0;
		}
		
		if ((currButtons & kButtonUp) && !(prevButtons & kButtonUp))
			CPasswordSelector_MoveUp(PasswordSelector);
		
		if ((currButtons & kButtonDown) && !(prevButtons & kButtonDown))
			CPasswordSelector_MoveDown(PasswordSelector);
		
		if ((currButtons & kButtonLeft) && !(prevButtons & kButtonLeft))
			CPasswordSelector_MoveLeft(PasswordSelector);
		
		if ((currButtons & kButtonRight) && !(prevButtons & kButtonRight))
			CPasswordSelector_MoveRight(PasswordSelector);
		
		/*SDL_Rect aDstRect;
		SDL_BlitSurface(Background,NULL,Screen,NULL);
		SDL_Color Color1 = {0,0,0,0};
		if (strlen(Password) > 0)
		{
			Text = TTF_RenderText_Solid(font,Password,Color1);
			
			aDstRect.x = Screen->w / 2 - Text->w / 2;
			aDstRect.y = 37;
			aDstRect.w = Text->w;
			aDstRect.h = Text->h;
			SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
			pd->graphics->freeBitmap(Text);
		}*/
		pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
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
					/*Text = TTF_RenderText_Solid(font, &Letter[0],Color1);
					aDstRect.x = XOffsetPassword + LetterX * 35;
					aDstRect.y = YOffsetPassword + LetterY * 35;
					aDstRect.w = Text->w;
					aDstRect.h = Text->h;
					SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
					pd->graphics->freeBitmap(Text);*/
					pd->graphics->drawText(&Letter[0], 1, kASCIIEncoding, XOffsetPassword + LetterX * 35, XOffsetPassword + LetterY * 35);
				}
			}
		CPasswordSelector_Draw(PasswordSelector);
	}
	
	if(GameState != GSPasswordEntry)
		PassWordEntryDeInit();
}
