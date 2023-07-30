
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "../commonvars.h"
#include "gamecommon.h"


void WriteText(SDL_Surface* Surface,TTF_Font* FontIn,char* Tekst,int NrOfChars,int X,int Y,int YSpacing,SDL_Color ColorIn)
{
	char List[100][255];
	int Lines,Teller,Chars;
	SDL_Rect aDstRect;
	SDL_Surface* TmpSurface;
	Lines = 0;
	Chars = 0;
	for (Teller=0;Teller<NrOfChars;Teller++)
	{
		if(Lines > 100)
			break;
		if((Tekst[Teller] == '\n') || (Chars==255))
		{
			List[Lines][Chars]='\0';
			Lines++;
			Chars = 0;
		}
		else
		{
		 	List[Lines][Chars]=Tekst[Teller];
		 	Chars++;
		}
	}
	List[Lines][Chars] = '\0';
	for (Teller=0;Teller <= Lines;Teller++)
	{
		if(strlen(List[Teller]) > 0)
		{
			TmpSurface = TTF_RenderText_Solid(FontIn,List[Teller],ColorIn);
			aDstRect.x = X;
			aDstRect.y = Y + (Teller) * TTF_FontLineSkip(FontIn) + (Teller*YSpacing);
			aDstRect.w = TmpSurface->w;
			aDstRect.h = TmpSurface->h;
			SDL_BlitSurface(TmpSurface,NULL,Surface,&aDstRect);
			SDL_FreeSurface(TmpSurface);
		}
	}
}

int GetLevel(char *Password)
{
	int Result,Teller;
	Result = -1;
	for (Teller = 0;Teller < 36;Teller++)
	{
		if (strcmp(Password,LevelPasswords[Teller]) ==0)
		{
			Result = Teller;
			break;
		}
	}
	return Result;
}

void DrawPanel()
{
	const SDL_Color Color = {255,255,255,0};
	SDL_Rect aDstRect;
	char ChrText[100];
	sprintf(ChrText,"Room Number: %d",Level);
	Text = TTF_RenderText_Solid(font,ChrText,Color);
	aDstRect.x = 30;
	aDstRect.y = 0;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	SDL_FreeSurface(Text);
	sprintf(ChrText,"Time: %02llu:%02llu:%02llu",(EndTime - StartTime) / 3600, ((EndTime - StartTime)%3600)/60,(EndTime-StartTime)%60);
	Text = TTF_RenderText_Solid(font,ChrText,Color);
	aDstRect.x = 175;
	aDstRect.y = 0;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	SDL_FreeSurface(Text);
}

void DrawPlayField()
{
	int Layers,X,Y;
	SDL_Rect aDstRect;
	for (Layers = 0;Layers <= 1;Layers++)
		for (X=Cols-1;X>=0;X--)
			for(Y=Rows-1;Y>=0;Y--)
			{
				if (PlayField[Layers][X][Y] > 0)
				{
					aDstRect.x = XOffsetGame + X * BlockWidth;
					aDstRect.y = YOffsetGame + Y * BlockHeight;
					aDstRect.w = BlockWidth;
					aDstRect.h = BlockHeight;
					SDL_BlitSurface(BlockImages[PlayField[Layers][X][Y] -1],NULL,Screen,&aDstRect);
				}

				if (PlayField[Layers][X][Y] < 0)
				{
					aDstRect.x = XOffsetGame + X * BlockWidth;
					aDstRect.y = YOffsetGame + Y * BlockHeight;
					aDstRect.w = BlockWidth;
					aDstRect.h = BlockHeight;
					SDL_BlitSurface(BorderImages[abs(PlayField[Layers][X][Y]) -1],NULL,Screen,&aDstRect);
				}
			}
}


void LoadImages()
{
	int teller;
	char FileName[FILENAME_MAX];
	for (teller=0;teller<BlockCount;teller++)
	{
		sprintf(FileName,"./graphics/block%d.png",teller+1);
		BlockImages[teller] = IMG_Load(FileName);
	}
	for (teller=0;teller<BorderCount;teller++)
	{
		sprintf(FileName,"./graphics/border%d.png",teller+1);
		BorderImages[teller] = IMG_Load(FileName);
		SDL_SetColorKey(BorderImages[teller],SDL_RLEACCEL | SDL_SRCCOLORKEY,SDL_MapRGB(BorderImages[teller]->format,255,0,255));
	}
    RoomBackground = IMG_Load("./graphics/roombackground.png");
 	StageClearKader = IMG_Load("./graphics/stageclearkader.png");
 	SDL_SetColorKey(StageClearKader,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(StageClearKader->format,255,0,255));
 	SDL_SetAlpha(StageClearKader,SDL_SRCALPHA,225);
 	Bridge = IMG_Load("./graphics/bridge.png");
 	SDL_SetColorKey(Bridge,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(Bridge->format,255,0,255));
}

void UnloadImages()
{
	int teller;
	for (teller=0;teller<BlockCount;teller++)
	{
		SDL_FreeSurface(BlockImages[teller]);
	}
	for (teller=0;teller<BorderCount;teller++)
	{
		SDL_FreeSurface(BorderImages[teller]);
	}
	SDL_FreeSurface(RoomBackground);
	SDL_FreeSurface(StageClearKader);
	SDL_FreeSurface(Bridge);
}

void UnloadSounds()
{
 	int teller;
 	for(teller=0;teller < NROFSOUNDS;teller++)
 	{
		Mix_FreeChunk(Sounds[teller]);
 	}
}

void LoadSounds()
{
	Sounds[SND_RotateBlock] = Mix_LoadWAV("./sounds/rotate.wav");
 	Sounds[SND_DropBlock] = Mix_LoadWAV("./sounds/drop.wav");
 	Sounds[SND_FlipBlock] = Mix_LoadWAV("./sounds/rotate.wav");
 	Sounds[SND_PickupBlock] = Mix_LoadWAV("./sounds/pickup.wav");
 	Sounds[SND_Error] = Mix_LoadWAV("./sounds/error.wav");
 	Sounds[SND_Menu] = Mix_LoadWAV("./sounds/menu.wav");
 	Sounds[SND_Select] = Mix_LoadWAV("./sounds/select.wav");
 	Sounds[SND_Bridge] = Mix_LoadWAV("./sounds/bridge.wav");
 	Sounds[SND_StageEnd] = Mix_LoadWAV("./sounds/stageend.wav");
 	Sounds[SND_Elf] = Mix_LoadWAV("./sounds/elf.wav");
}

void LoadMusic()
{
 	Music[MUS_Title] = Mix_LoadMUS("./music/title.ogg");
 	Music[MUS_Game1] = Mix_LoadMUS("./music/game1.ogg");
 	Music[MUS_Game2] = Mix_LoadMUS("./music/game2.ogg");
 	Music[MUS_Oldman] = Mix_LoadMUS("./music/oldman.ogg");
 	Music[MUS_Stage] = Mix_LoadMUS("./music/stage.ogg");
}


void UnloadMusic()
{
 	int teller;
    Mix_HaltMusic();
	for(teller=0;teller<NROFMUSIC;teller++)
	{
		Mix_FreeMusic(Music[teller]);
	}
}


void LoadSettings()
{
 	FILE *SettingsFile;
 	int Value=1;
 	SettingsFile = fopen("./settings.dat","r");
 	if(SettingsFile)
 	{
		fscanf(SettingsFile,"SoundOn=%d\n",&Value);
		if (Value > 0)
			SoundEnabled = true;
		else
			SoundEnabled = false;
		fscanf(SettingsFile,"MusicOn=%d\n",&Value);
		if (Value > 0)
			MusicEnabled = true;
		else
			MusicEnabled = false;
		fclose(SettingsFile);
 	}
 	else
 	{
 		SoundEnabled = true;
		MusicEnabled = true;
	}
}

void SaveSettings()
{
 	FILE *SettingsFile;
 	SettingsFile = fopen("./settings.dat","w");
 	if(SettingsFile)
 	{
		if(SoundEnabled)
			fprintf(SettingsFile,"SoundOn=%d\n",1);
		else
			fprintf(SettingsFile,"SoundOn=%d\n",0);
		if (MusicEnabled)
			fprintf(SettingsFile,"MusicOn=%d\n",1);
		else
			fprintf(SettingsFile,"MusicOn=%d\n",0);
		fclose(SettingsFile);
 	}
}