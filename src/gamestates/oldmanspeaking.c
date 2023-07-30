#include <pd_api.h>
#include <stdbool.h>
#include "../pd_helperfuncs.h"
#include "../sound.h"
#include "../gameobjects/cfairy.h"
#include "../commonvars.h"
#include "gamecommon.h"
#include "oldmanspeaking.h"

const char* const Tekst[5] = {"Welcome to the world of\npuzzle land!\nIn level one we'll start with\nsimple three-block\ncombinations ...$When you've mastered level\none, we'll add another block.\nHang in there!",
								  "Congratulations you made it!\nNow we'll boggle your mind,\nthere are 2339 diffrent\nconfigurations in this stage!$Don't give up!\nRelax!",
								  "Hah! This next stage will\nsurprise you!\nYou now have 12 diffrent\nshapes to work with ...$Show me how far you can\ngo dude!",
								  "Well, well, well.\nYou seem to have made it all\nthis way! As a token of our\nappreciation for your skill,...$Here's another square block!\nTake the square block, and try\nit for the last level!$It looks simple, but there are\n16146 configurations!\n\nHey dude, you're on it again.",
          						  "Congratulations you made it!\nYou've earned the password\nfor the level select!\nthe password is 'davy'"};
int Lines,Chars,TextDelay,PageNr,TekstNr;
size_t NrOfChars;
size_t Teller;
char List[100][255];


    
void OldManSpeakingInit()
{
	Background = NULL;
	Fairy = CFairy_Create(240,175,6);
	switch (Level)
	{
		case 0:
		case 11:
		case 12:
		case 35:
		case 36:
			SelectMusic(musOldman);
			TextDelay = 0;
			NrOfChars = 0;
			Lines = 0;
			Chars =0;
			PageNr = 0;
			switch (Level)
			{
				case 0:
					TekstNr = 0;
					break;
				case 11:
					TekstNr = 1;
					break;
				case 12:
					TekstNr = 2;
					break;
				case 35:
					TekstNr = 3;
					break;
				case 36:
					TekstNr = 4;
					break;
				default: TekstNr = 0;
			}
			Background = loadImageAtPath("graphics/oldman");
			for(Teller=0;Teller<strlen(Tekst[TekstNr]);Teller++)
			{
				if (Tekst[TekstNr][Teller] == '$')
				{
					List[Lines][Chars] = '\0';
					Lines++;
					Chars=0;
				}
				else
				{
					List[Lines][Chars] = Tekst[TekstNr][Teller];
					Chars++;
				}
			}
			List[Lines][Chars] = '\0';
		break;
		default:
			GameState = GSNextStageInit;
			break;
	}
}

void OldManSpeakingDeInit()
{
	if(Background)
		pd->graphics->freeBitmap(Background);
	CFairy_Destroy(Fairy);
}


void OldManSpeaking()
{
	if(GameState == GSOldManSpeakingInit)
	{
		OldManSpeakingInit();
		if(GameState == GSOldManSpeakingInit)
			GameState -= GSInitDiff;
	}

	if (GameState == GSOldManSpeaking)
	{
		pd->graphics->clear(kColorWhite);
		pd->graphics->setBackgroundColor(kColorWhite);
		pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
		{
			if (PageNr < Lines)
			{
				PageNr++;
				NrOfChars = 0;
			}
			else
				if (Level < 36)
					GameState = GSNextStageInit;
				else
					GameState = GSCreditsInit;
		}
			/*			case SDLK_ESCAPE:
							Mix_HaltMusic();
							GameState = GSTitleScreenInit;
							break;
			*/
		
		if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
		{
			if (Level < 36)
				GameState = GSNextStageInit;
			else
				GameState = GSCreditsInit;
		}
		pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);

		CFairy_Draw(Fairy);
		TextDelay++;
		if (TextDelay == 2)
		{
			if (NrOfChars < strlen(List[PageNr]))
				NrOfChars++;
			TextDelay = 0;
		}
		pd->graphics->pushContext(NULL);
		pd->graphics->setFont(NULL);
		pd->graphics->drawText(List[PageNr], NrOfChars, kASCIIEncoding, 50, 50);
		pd->graphics->popContext();
	}
	
	if(GameState != GSOldManSpeaking)
		OldManSpeakingDeInit();
}
