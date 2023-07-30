#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "gamestates/game.h"
#include "gamestates/stageclear.h"
#include "gamestates/nextstage.h"
#include "gamestates/options.h"
#include "gamestates/stageselect.h"
#include "gamestates/oldmanspeaking.h"
#include "gamestates/passwordentry.h"
#include "gamestates/titlescreen.h"
#include "gamestates/intro.h"
#include "gamestates/titlescreen.h"
#include "gamestates/credits.h"
#include "gamestates/gamecommon.h"
#include "commonvars.h"

int main(int argv, char** args)
{
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == 0)
	{
		printf("SDL Succesfully initialized\n");
		Screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT,16, SDL_SWSURFACE );
        if(Screen)
		{
		 	SDL_ShowCursor(SDL_DISABLE);
			{
				if (Mix_OpenAudio(22050,AUDIO_S16,MIX_DEFAULT_CHANNELS,1024) < 0)
				{
					GlobalSoundEnabled = false;
					printf("Failed to initialise sound!\n");
					printf("%s\n",Mix_GetError());
				}
				else
				{
			 		printf("Audio Succesfully initialised!\n");
				}
		    	LoadSounds();
				LoadMusic();
				LoadSettings();
				LoadImages();
				if (TTF_Init() == 0)
				{
					printf("Succesfully initialized TTF\n");
					font = TTF_OpenFont("font.ttf",25);
					if (font)
					{
						printf("Succesfully Loaded font\n");
						TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
						Hand = CHand_Create();
						OldTime = 0;
						while (GameState != GSQuit)
						{
							switch(GameState)
							{
								case GSIntroInit :
								case GSIntro :
									Intro();
									break;
								case GSTitleScreenInit :
								case GSTitleScreen :
									TitleScreen();
									break;
								case GSOldManSpeakingInit :
								case GSOldManSpeaking :
									OldManSpeaking();
									break;
								case GSPasswordEntryInit :
								case GSPasswordEntry :
									PasswordEntry();
									break;
								case GSCreditsInit :
								case GSCredits :
									Credits();
									break;
								case GSOptionsInit :
								case GSOptions :
									Options();
									break;
								case GSGameInit :
								case GSGame :
									Game();
									break;
								case GSStageClearInit:
								case GSStageClear:
									StageClear();
									break;
								case GSNextStageInit:
								case GSNextStage:
									if (Level ==0)
										NextStageLevel0();
									else
										NextStageLevel1to35();
									break;
								case GSStageSelectInit:
								case GSStageSelect:
									StageSelect();
									break;
								default:
									break;
							}
							if ((SDL_GetTicks() - OldTime) > 0)
							{	
								const SDL_Color Color = {255,255,255,0};							
								char fps[20];
								sprintf(fps,"fps: %d",1000 /(SDL_GetTicks() - OldTime));
								OldTime=SDL_GetTicks();
								SDL_Surface * fpsText = TTF_RenderText_Solid(font,fps,Color);
								SDL_Rect DstRect = {0, WINDOW_HEIGHT - fpsText->h - 2, fpsText->w, fpsText->h};
								SDL_FillRect(Screen, &DstRect, SDL_MapRGB(Screen->format, 0, 0, 0));
								SDL_BlitSurface(fpsText,NULL,Screen,&DstRect);
								SDL_FreeSurface(fpsText);
							}
							SDL_Flip(Screen);
							SDL_Delay(1000/15);
						}
						CHand_Destroy(Hand);
						TTF_CloseFont(font);
				    	font=NULL;
					}
					else
					{
						printf("Failed to Load font\n");
					}
					TTF_Quit();
				}
				else
				{
					printf("Failed to initialize TTF\n");
				}
				SDL_FreeSurface(Screen);
				Screen=NULL;
				Mix_CloseAudio();
				UnloadSounds();
				UnloadMusic();
				UnloadImages();
				SaveSettings();
			}
		}
		else
		{
			printf("Failed to Set Videomode %dx%dx32\n",WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		SDL_Quit();
	}
	else
	{
		printf("Couldn't initialise SDL!\n");
	}
	return 0;
}
