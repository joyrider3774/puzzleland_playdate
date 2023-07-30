#include <pd_api.h>
#include <stdbool.h>
#include "../sound.h"
#include "../pd_helperfuncs.h"
#include "../gameobjects/cspaceship.h"
#include "../gameobjects/ccloud.h"
#include "../gameobjects/cstageblock.h"
#include "../gameobjects/cplayer.h"
#include "../gameobjects/cfairy.h"
#include "../commonvars.h"
#include "nextstage.h"
	
CStageBlock *StageBlock;
CPlayer* Player;
CCloud* Cloud1;
CCloud* Cloud2;
CCloud* Cloud3;
CCloud* Cloud4;
CSpaceShip* SpaceShip;

bool BridgeShown = false;
bool BridgeDrawing = false;
int BridgeDrawnWidth = 0;


void NextStageLevel1to35Init()
{
	BridgeShown = false;
	BridgeDrawing = false;
	BridgeDrawnWidth = 0;

	StageBlock = CStageBlock_Create();
	Player = CPlayer_Create(30,167,30,268);
	Cloud1 = CCloud_Create(259,15,-0.40,Big);
	Cloud2 = CCloud_Create(185,45,-0.25,Small);
	Cloud3 = CCloud_Create(134,7,-0.40,Big);
	Cloud4 = CCloud_Create(50,50,-0.25,Small);
	SpaceShip = CSpaceShip_Create();
	Fairy = CFairy_Create(172,160,3);
	Background = loadImageAtPath("graphics/betweenstage");
	SelectMusic(musStage);
	switch (Level)
	{
		case 1:
			CStageBlock_Load(StageBlock, 1);
			break;
  		case 2:
			CStageBlock_Load(StageBlock,2);
  			break;
  		case 3:
			CStageBlock_Load(StageBlock,3);
  			break;
  		case 4:
			CStageBlock_Load(StageBlock,4);
  			break;
  		case 5:
			CStageBlock_Load(StageBlock,5);
  			break;
  		case 6:
			CStageBlock_Load(StageBlock,6);
  			break;
  		case 8:
  			CStageBlock_Load(StageBlock,7);
  			break;
  		case 9:
  			CStageBlock_Load(StageBlock,8);
  			break;
  		case 11:

  			CStageBlock_Load(StageBlock,9);
  			break;
  		case 35:
  			CStageBlock_Load(StageBlock,10);
  			break;
  		default: Fairy->Hidden = true;
	}
}

void NextStageLevel1to35DeInit()
{
	//Mix_HaltMusic();
	pd->graphics->freeBitmap(PrevLevel);
 	pd->graphics->freeBitmap(NextLevel);
	pd->graphics->freeBitmap(Text);
	pd->graphics->freeBitmap(Background);
	CSpaceShip_destroy(SpaceShip);
	CFairy_Destroy(Fairy);
	CCloud_Destroy(Cloud1);
	CCloud_Destroy(Cloud2);
	CCloud_Destroy(Cloud3);
	CCloud_Destroy(Cloud4);
	CPlayer_Destroy(Player);
}

void NextStageLevel1to35()
{
	if(GameState == GSNextStageInit)
	{
		NextStageLevel1to35Init();
		GameState -= GSInitDiff;
	}
	
	if (GameState == GSNextStage)
	{
		/*case SDLK_ESCAPE :
			GameState = GSTitleScreenInit;
		break;*/
		if (((currButtons & kButtonA) && !(prevButtons & kButtonA)) ||
			((currButtons & kButtonB) && !(prevButtons & kButtonB)))
		{
			if(CPlayer_GetX(Player) > 265)
				Player->State = EnterBuilding;
			if(CPlayer_GetX(Player) < 32)
				Player->State = EnterBuilding;
		}

		pd->graphics->clear(kColorBlack);
		pd->graphics->setBackgroundColor(kColorBlack);
		pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);
		CCloud_Move(Cloud1);
		CCloud_Draw(Cloud1);
		CCloud_Move(Cloud2);
		CCloud_Draw(Cloud2);
		CCloud_Move(Cloud3);
		CCloud_Draw(Cloud3);
		CCloud_Move(Cloud4);
		CCloud_Draw(Cloud4);

		if (!BridgeShown)
		{
			if(!BridgeDrawing)
			{
				if(CPlayer_GetX(Player) > 92)
				{
					BridgeDrawing = true;
					playBridgeSound();
				}
			}
			else
			{
			    int srcx, srcy, dstx, dsty, srcw, srch, bridgew, bridgeh;
				pd->graphics->getBitmapData(Bridge, &bridgew, &bridgeh, NULL, NULL, NULL);
				srcx = 0;
				srcy = 0;
				srcw = BridgeDrawnWidth;
				srch = bridgeh;
				dstx = 111;
				dsty = 188;
				BridgeDrawnWidth = BridgeDrawnWidth + 5;
				if (BridgeDrawnWidth >= bridgew)
				{
					BridgeDrawing = false;
					BridgeShown = true;
					srcw = bridgew;
				}
				
				DrawBitmapSrcRec(Bridge, dstx, dsty, srcx, srcy, srcw, srch, kBitmapUnflipped);
			}
		}
		else
		{
			pd->graphics->drawBitmap(Bridge,111, 188, kBitmapUnflipped);
			//SDL_BlitSurface(Bridge, NULL, Screen, &BridgeDstRect);
		}
		CPlayer_Move(Player);
		CPlayer_Draw(Player);
		switch(Level)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 8:
			case 9:
			case 11:
			case 35:
				CFairy_Draw(Fairy);

				if((Player->State != LookingUp) && (! Fairy->Hidden) && (CPlayer_GetX(Player) + CPlayer_GetWidth(Player) >= CFairy_GetX(Fairy)))
				{
					playElfSound();
					Fairy->Hidden = true;
					Player->State = LookingUp;
				}
				if (Player->State == LookingUp)
				{
					CStageBlock_Draw(StageBlock);
					CStageBlock_Move(StageBlock);
					if( CStageBlock_GetY(StageBlock) + CStageBlock_GetHeight(StageBlock) >= CPlayer_GetY(Player))
					{
						Player->State = Waiting;
						StageBlock->Hidden = true;
					}
				}
				break;
		}

		CSpaceShip_Move(SpaceShip);
		int textw = pd->graphics->getTextWidth(Mini2X, LevelPasswords[Level], strlen(LevelPasswords[Level]), kASCIIEncoding, 0);
		if (CSpaceShip_GetX(SpaceShip) > (WINDOW_WIDTH >> 1) - (textw >> 1))
		{
			pd->graphics->fillRect((WINDOW_WIDTH >> 1) - (textw >> 1) - 2, 32, textw + 4, 20, kColorWhite);
			pd->graphics->pushContext(NULL);
			pd->graphics->setFont(Mini2X);
			pd->graphics->drawText(LevelPasswords[Level], strlen(LevelPasswords[Level]), kASCIIEncoding, (WINDOW_WIDTH >> 1) - (textw >> 1), 34);
			pd->graphics->popContext();
		}
		CSpaceShip_Draw(SpaceShip);
		
		pd->graphics->pushContext(NULL);
		pd->graphics->setFont(NULL);
		char* ChrLevel;
		pd->system->formatString(&ChrLevel, "%02d", Level + 1);
		pd->graphics->drawText(ChrLevel, strlen(ChrLevel), kASCIIEncoding, 270, 110);
		pd->system->realloc(ChrLevel, 0);

		pd->system->formatString(&ChrLevel, "%02d", Level);
		pd->graphics->drawText(ChrLevel, strlen(ChrLevel), kASCIIEncoding, 31, 110);
		pd->system->realloc(ChrLevel, 0);
		pd->graphics->popContext();
		
		if (Player->State == EnteredBuilding)
		{
			if(CPlayer_GetX(Player) > 265)
				Level++;
			GameState = GSGameInit;
		}
	}
	
	if(GameState != GSNextStage)
		NextStageLevel1to35DeInit();
}

void NextStageLevel0Init()
{
	Player = CPlayer_Create(225,167,225,268);
	Cloud1 = CCloud_Create(259,15,-0.40,Big);
	Cloud2 = CCloud_Create(185,45,-0.25,Small);
	Cloud3 = CCloud_Create(134,7,-0.40,Big);
	Cloud4 = CCloud_Create(50,50,-0.25,Small);
	Background = loadImageAtPath("graphics/betweenstagelevel1");
	SelectMusic(musStage);
}

void NextStageLevel0DeInit()
{
	pd->graphics->freeBitmap(Text);
	pd->graphics->freeBitmap(Background);
	CPlayer_Destroy(Player);
	CCloud_Destroy(Cloud1);
	CCloud_Destroy(Cloud2);
	CCloud_Destroy(Cloud3);
	CCloud_Destroy(Cloud4);
}

void NextStageLevel0()
{
	if(GameState == GSNextStageInit)
	{
		NextStageLevel0Init();
		GameState -= GSInitDiff;
	}	
	
	if (((currButtons & kButtonA) && !(prevButtons & kButtonA)) ||
		((currButtons & kButtonB) && !(prevButtons & kButtonB)))
	{
		if (CPlayer_GetX(Player) > 265)
			Player->State = EnterBuilding;
	}
	pd->graphics->clear(kColorBlack);
	pd->graphics->setBackgroundColor(kColorBlack);
	pd->graphics->setClipRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	pd->graphics->drawBitmap(Background, 0, 0, kBitmapUnflipped);

	pd->graphics->pushContext(NULL);
	pd->graphics->setFont(NULL);
	char* ChrLevel;
	pd->system->formatString(&ChrLevel, "%02d", Level + 1);
	pd->graphics->drawText(ChrLevel, strlen(ChrLevel), kASCIIEncoding, 270, 110);
	pd->system->realloc(ChrLevel, 0);
	pd->graphics->popContext();


	CCloud_Move(Cloud1);
	CCloud_Draw(Cloud1);
	CCloud_Move(Cloud2);
	CCloud_Draw(Cloud2);
	CCloud_Move(Cloud3);
	CCloud_Draw(Cloud3);
	CCloud_Move(Cloud4);
	CCloud_Draw(Cloud4);
	CPlayer_Move(Player);
	CPlayer_Draw(Player);
	if (Player->State == EnteredBuilding)
	{
		if(CPlayer_GetX(Player) > 265)
			Level++;
		GameState = GSGameInit;
	}

	if(GameState != GSNextStage)
		NextStageLevel0DeInit();
}
