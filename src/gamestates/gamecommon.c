
#include <pd_api.h>
#include <string.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "gamecommon.h"



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
	/*const SDL_Color Color = {255,255,255,0};
	SDL_Rect aDstRect;
	char ChrText[100];
	sprintf(ChrText,"Room Number: %d",Level);
	Text = TTF_RenderText_Solid(font,ChrText,Color);
	aDstRect.x = 30;
	aDstRect.y = 0;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	pd->graphics->freeBitmap(Text);
	sprintf(ChrText,"Time: %02llu:%02llu:%02llu",(EndTime - StartTime) / 3600, ((EndTime - StartTime)%3600)/60,(EndTime-StartTime)%60);
	Text = TTF_RenderText_Solid(font,ChrText,Color);
	aDstRect.x = 175;
	aDstRect.y = 0;
	aDstRect.w = Text->w;
	aDstRect.h = Text->h;
	SDL_BlitSurface(Text,NULL,Screen,&aDstRect);
	pd->graphics->freeBitmap(Text);*/

	char* ChrText;
	pd->graphics->setDrawMode(kDrawModeInverted);
	pd->system->formatString(&ChrText, "Room Number: %d", Level);
	pd->graphics->drawText(ChrText, strlen(ChrText), kASCIIEncoding, 30, 0);
	pd->system->realloc(ChrText, 0);
	pd->system->formatString(&ChrText, "Time: %02u:%02u:%02u", (EndTime - StartTime) / 3600, ((EndTime - StartTime) % 3600) / 60, (EndTime - StartTime) % 60);
	pd->graphics->drawText(ChrText, strlen(ChrText), kASCIIEncoding, 175, 0);
	pd->system->realloc(ChrText, 0);
	pd->graphics->setDrawMode(kDrawModeCopy);
}

void DrawPlayField()
{
	int Layers,X,Y;
	//SDL_Rect aDstRect;
	for (Layers = 0;Layers <= 1;Layers++)
		for (X=Cols-1;X>=0;X--)
			for(Y=Rows-1;Y>=0;Y--)
			{
				if (PlayField[Layers][X][Y] > 0)
				{
					/*aDstRect.x = XOffsetGame + X * BlockWidth;
					aDstRect.y = YOffsetGame + Y * BlockHeight;
					aDstRect.w = BlockWidth;
					aDstRect.h = BlockHeight;
					SDL_BlitSurface(BlockImages[PlayField[Layers][X][Y] -1],NULL,Screen,&aDstRect);*/
					pd->graphics->drawBitmap(BlockImages[PlayField[Layers][X][Y] - 1], XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, kBitmapUnflipped);
				}

				if (PlayField[Layers][X][Y] < 0)
				{
					//aDstRect.x = XOffsetGame + X * BlockWidth;
					//aDstRect.y = YOffsetGame + Y * BlockHeight;
					//aDstRect.w = BlockWidth;
					//aDstRect.h = BlockHeight;
					//SDL_BlitSurface(BorderImages[abs(PlayField[Layers][X][Y]) -1],NULL,Screen,&aDstRect);
					pd->graphics->drawBitmap(BorderImages[abs(PlayField[Layers][X][Y]) - 1], XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, kBitmapUnflipped);

				}
			}
}


void LoadImages()
{
	int teller;
	char* FileName;
	for (teller=0;teller<BlockCount;teller++)
	{
		pd->system->formatString(&FileName,"graphics/block%d",teller+1);
		BlockImages[teller] = loadImageAtPath(FileName);
	}
	for (teller=0;teller<BorderCount;teller++)
	{
		pd->system->formatString(&FileName, "graphics/border%d",teller+1);
		BorderImages[teller] = loadImageAtPath(FileName);
		//SDL_SetColorKey(BorderImages[teller],SDL_RLEACCEL | SDL_SRCCOLORKEY,SDL_MapRGB(BorderImages[teller]->format,255,0,255));
	}
    RoomBackground = loadImageAtPath("graphics/roombackground");
 	StageClearKader = loadImageAtPath("graphics/stageclearkader");
 	//SDL_SetColorKey(StageClearKader,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(StageClearKader->format,255,0,255));
 	//SDL_SetAlpha(StageClearKader,SDL_SRCALPHA,225);
 	Bridge = loadImageAtPath("graphics/bridge");
 	//SDL_SetColorKey(Bridge,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(Bridge->format,255,0,255));
}

void UnloadImages()
{
	int teller;
	for (teller=0;teller<BlockCount;teller++)
	{
		pd->graphics->freeBitmap(BlockImages[teller]);
	}
	for (teller=0;teller<BorderCount;teller++)
	{
		pd->graphics->freeBitmap(BorderImages[teller]);
	}
	pd->graphics->freeBitmap(RoomBackground);
	pd->graphics->freeBitmap(StageClearKader);
	pd->graphics->freeBitmap(Bridge);
}


void LoadSettings()
{
 //	FILE *SettingsFile;
 //	int Value=1;
 //	SettingsFile = fopen("./settings.dat","r");
 //	if(SettingsFile)
 //	{
	//	fscanf(SettingsFile,"SoundOn=%d\n",&Value);
	//	if (Value > 0)
	//		SoundEnabled = true;
	//	else
	//		SoundEnabled = false;
	//	fscanf(SettingsFile,"MusicOn=%d\n",&Value);
	//	if (Value > 0)
	//		MusicEnabled = true;
	//	else
	//		MusicEnabled = false;
	//	fclose(SettingsFile);
 //	}
 //	else
 //	{
 //		SoundEnabled = true;
	//	MusicEnabled = true;
	//}
}

void SaveSettings()
{
 	//FILE *SettingsFile;
 	//SettingsFile = fopen("./settings.dat","w");
 	//if(SettingsFile)
 	//{
		//if(SoundEnabled)
		//	fprintf(SettingsFile,"SoundOn=%d\n",1);
		//else
		//	fprintf(SettingsFile,"SoundOn=%d\n",0);
		//if (MusicEnabled)
		//	fprintf(SettingsFile,"MusicOn=%d\n",1);
		//else
		//	fprintf(SettingsFile,"MusicOn=%d\n",0);
		//fclose(SettingsFile);
 	//}
}