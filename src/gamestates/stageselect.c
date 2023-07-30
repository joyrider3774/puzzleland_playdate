#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include "../gameobjects/cstageselectselector.h"
#include "../commonvars.h"
#include "stageselect.h"


CStageSelectSelector *StageSelectSelector;

void StageSelectInit()
{
	StageSelectSelector = CStageSelectSelector_Create();
	Background = IMG_Load("./graphics/paper.png");
	SDL_PollEvent(&Event);
}

void StageSelectDeInit()
{
	SDL_FreeSurface(Background);
	CStageSelectSelector_destroy(StageSelectSelector);
}

void StageSelect()
{
	if(GameState == GSStageSelectInit)
	{
		StageSelectInit();
		GameState -= GSInitDiff;
	}

	while(SDL_PollEvent(&Event))
	{
		if( Event.type == SDL_KEYDOWN)
		{
			switch (Event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					GameState = GSTitleScreenInit;
					break;
				case SDLK_x:
					if (GlobalSoundEnabled && SoundEnabled)
						Mix_PlayChannel(-1,Sounds[SND_Select],0);
					Level = CStageSelectSelector_GetSelection(StageSelectSelector);
					GameState = GSOldManSpeakingInit;
					Mix_HaltMusic();
					break;
				case SDLK_UP:
					CStageSelectSelector_MoveUp(StageSelectSelector);
					break;
				case SDLK_DOWN:
					CStageSelectSelector_MoveDown(StageSelectSelector);
					break;
				case SDLK_LEFT:
					CStageSelectSelector_MoveLeft(StageSelectSelector);
					break;
				case SDLK_RIGHT:
					CStageSelectSelector_MoveRight(StageSelectSelector);
					break;
				default:
					break;
			}
		}
	}
	SDL_Rect aDstRect;
	SDL_Color Color1 = {0,0,0,0};
	SDL_BlitSurface(Background,NULL,Screen,NULL);
	Text = TTF_RenderText_Solid(font,"ROOM SELECT",Color1);
	aDstRect.x = Screen->w / 2 - Text->w / 2;
	aDstRect.y = 20;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	SDL_FreeSurface(Text);
	int Teller;
	char ChrRoom[10];
	for (Teller=0;Teller< 36;Teller++)
	{
		sprintf(ChrRoom,"Room %d",Teller+1);
		Text = TTF_RenderText_Solid(font,ChrRoom,Color1);
		aDstRect.x = XOffsetStageSelect + (Teller % 3) * 82;
		aDstRect.y = YOffsetStageSelect + (Teller / 3) * 14;
		aDstRect.w = Text->w;
		aDstRect.h = Text->h;
		SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
		SDL_FreeSurface(Text);
	}
	CStageSelectSelector_Draw(StageSelectSelector);

	if(GameState != GSStageSelect)
		StageSelectDeInit();
}
