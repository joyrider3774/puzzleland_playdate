#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
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
	Background = IMG_Load("./graphics/paper.png");
	SDL_PollEvent(&Event);
}

void PassWordEntryDeInit()
{
	SDL_FreeSurface(Background);
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
		SDL_Delay(250);
		if (GetLevel(Password) == -1)
		{
			Password[0] = ' ';
			Password[1] = ' ';
			Password[2] = ' ';
			Password[3] = ' ';
			if (GlobalSoundEnabled && SoundEnabled)
				Mix_PlayChannel(-1,Sounds[SND_Error],0);
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
				Mix_HaltMusic();
			}
	}
	if(GameState == GSPasswordEntry)
	{
		while(SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_KEYDOWN)
			{
				switch(Event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						GameState = GSTitleScreenInit;
						break;
					case SDLK_x:
						Password[CharNr] = Letters[CPasswordSelector_GetY(PasswordSelector)][CPasswordSelector_GetX(PasswordSelector)];
						if (GlobalSoundEnabled && SoundEnabled)
							Mix_PlayChannel(-1,Sounds[SND_Select],0);
						CharNr++;
						if (CharNr > 3)
							CharNr = 0;
						break;
					case SDLK_UP:
						CPasswordSelector_MoveUp(PasswordSelector);
						break;
					case SDLK_DOWN:
						CPasswordSelector_MoveDown(PasswordSelector);
						break;
					case SDLK_LEFT:
						CPasswordSelector_MoveLeft(PasswordSelector);
						break;
					case SDLK_RIGHT:
						CPasswordSelector_MoveRight(PasswordSelector);
						break;
					default:
						break;
				}
			}
		}
		SDL_Rect aDstRect;
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
			SDL_FreeSurface(Text);
		}
		int LetterX,LetterY;
		for (LetterY = 0 ;LetterY < LetterRows;LetterY++)
			for (LetterX = 0;LetterX < LetterCols;LetterX++)
			{
				if(Letters[LetterY][LetterX] != '0')
				{
					char Letter[2] = "\0";
					Letter[0] = Letters[LetterY][LetterX];
					Text = TTF_RenderText_Solid(font, &Letter[0],Color1);
					aDstRect.x = XOffsetPassword + LetterX * 35;
					aDstRect.y = YOffsetPassword + LetterY * 35;
					aDstRect.w = Text->w;
					aDstRect.h = Text->h;
					SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
					SDL_FreeSurface(Text);
				}
			}
		CPasswordSelector_Draw(PasswordSelector);
	}
	
	if(GameState != GSPasswordEntry)
		PassWordEntryDeInit();
}
