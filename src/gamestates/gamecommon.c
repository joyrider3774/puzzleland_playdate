
#include <pd_api.h>
#include <string.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "../sound.h"
#include "gamecommon.h"


void MenuItemCallback(void* userdata)
{
	if (userdata == &menuItem1)
	{
		GameState = GSTitleScreenInit;
		stopTextSound();
	}

	if (userdata == &menuItem2)
	{
		NeedGameReset = true;
	}
}

void DestroyMenuItems()
{
	if (menuItem1)
	{
		pd->system->removeMenuItem(menuItem1);
		menuItem1 = NULL;
	}

	if (menuItem2)
	{
		pd->system->removeMenuItem(menuItem2);
		menuItem2 = NULL;
	}

	if (menuItem3)
	{
		pd->system->removeMenuItem(menuItem3);
		menuItem3 = NULL;
	}
}

void CreateGameMenuItems()
{
	DestroyMenuItems();
	//TitleScreen
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Title Screen", MenuItemCallback, &menuItem1);
	}

	if (menuItem2 == NULL)
	{
		menuItem2 = pd->system->addMenuItem("Reset Room", MenuItemCallback, &menuItem2);
	}
}

void CreateOtherMenuItems()
{
	DestroyMenuItems();
	//TitleScreen
	if (menuItem1 == NULL)
	{
		menuItem1 = pd->system->addMenuItem("Title Screen", MenuItemCallback, &menuItem1);
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
	char* ChrText;
	pd->graphics->pushContext(NULL);
	pd->graphics->setFont(Ash);
	pd->graphics->setDrawMode(kDrawModeInverted);
	pd->system->formatString(&ChrText, "Room Number: %d", Level);
	pd->graphics->drawText(ChrText, strlen(ChrText), kASCIIEncoding, 30, 4);
	pd->system->realloc(ChrText, 0);
	pd->system->formatString(&ChrText, "Time: %02u:%02u:%02u", (EndTime - StartTime) / 3600, ((EndTime - StartTime) % 3600) / 60, (EndTime - StartTime) % 60);
	pd->graphics->drawText(ChrText, strlen(ChrText), kASCIIEncoding, 180, 4);
	pd->system->realloc(ChrText, 0);
	pd->graphics->popContext();
}

void DrawPlayField()
{
	int Layers,X,Y;
	for (Layers = 0;Layers <= 1;Layers++)
		for (X=Cols-1;X>=0;X--)
			for(Y=Rows-1;Y>=0;Y--)
			{
				if (PlayField[Layers][X][Y] > 0)
				{
					//simple line drawing of same type of blocks, this will form shapes which is way batter than what i had before
					pd->graphics->drawBitmap(BlockImage, XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, kBitmapUnflipped);
					if ((X == 0) || ((X > 0) && (PlayField[Layers][X - 1][Y] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth +1, YOffsetGame + Y * BlockHeight, XOffsetGame + X * BlockWidth+1, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
					}
					if ((X == Cols-1) || ((X < Cols-1) && (PlayField[Layers][X + 1][Y] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth + BlockWidth , YOffsetGame + Y * BlockHeight,  XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight, XOffsetGame + X * BlockWidth + BlockWidth-1, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
					}
					if ((Y == 0) || ((Y > 0) && (PlayField[Layers][X][Y-1] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight ,  XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight+1, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight+1, 1, kColorBlack);
					}
					if ((Y == Rows-1) || ((Y < Rows-1) && (PlayField[Layers][X][Y + 1] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight-1, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight-1, 1, kColorBlack);
					}
				}

				if (PlayField[Layers][X][Y] < 0)
				{
					pd->graphics->drawBitmap(BorderImages[abs(PlayField[Layers][X][Y]) - 1], XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight, kBitmapUnflipped);
					if ((X == Cols - 1) || ((X < Cols - 1) && (PlayField[Layers][X + 1][Y] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth + BlockWidth + 1, YOffsetGame + Y * BlockHeight+1, XOffsetGame + X * BlockWidth + BlockWidth + 1, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
					}
					if ((Y == Rows - 1) || ((Y < Rows - 1) && (PlayField[Layers][X][Y + 1] != PlayField[Layers][X][Y])))
					{
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight, 1, kColorBlack);
						pd->graphics->drawLine(XOffsetGame + X * BlockWidth+1, YOffsetGame + Y * BlockHeight + BlockHeight + 1, XOffsetGame + X * BlockWidth + BlockWidth, YOffsetGame + Y * BlockHeight + BlockHeight + 1, 1, kColorBlack);
					}
				}
			}
}


void LoadImages()
{
	int teller;
	char* FileName;
	BlockImage = loadImageAtPath("graphics/blockimage");
	for (teller=0;teller<BorderCount;teller++)
	{
		pd->system->formatString(&FileName, "graphics/border%d",teller+1);
		BorderImages[teller] = loadImageAtPath(FileName);
	}
    RoomBackground = loadImageAtPath("graphics/roombackground");
 	StageClearKader = loadImageAtPath("graphics/stageclearkader");
 	Bridge = loadImageAtPath("graphics/bridge");
}

void UnloadImages()
{
	int teller;
	for (teller=0;teller<BorderCount;teller++)
	{
		pd->graphics->freeBitmap(BorderImages[teller]);
	}
	pd->graphics->freeBitmap(BlockImage);
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