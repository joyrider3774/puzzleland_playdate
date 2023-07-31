#include <pd_api.h>
#include "../pd_helperfuncs.h"
#include "../commonvars.h"
#include "cplayer.h"

//Player anims
const int AnimLeft[6]= {12,11,10,9,8,7};
const int AnimRight[6]  = {1,2,3,4,5,6};
const int AnimEnterBuilding[4]  = {15,16,17,18};


CPlayer* CPlayer_Create(const int Xin,const int Yin,const int MinXin, const int MaxXin)
{
	CPlayer* Result = pd->system->realloc(NULL, sizeof(CPlayer));
 	Result->Image = loadImageAtPath("graphics/ryf-player");
 	Result->Shadow = loadImageAtPath("graphics/ryf-shadow");
 	Result->Y = Yin;
	Result->X = Xin;
 	Result->Width = 23;
 	Result->Height = 28;
 	Result->AnimCounter = 0;
 	Result->Delay = 0;
 	Result->AnimPhase = 0;
 	Result->MaxX = MaxXin;
 	Result->MinX = MinXin;
 	Result->State = Waiting;
	return Result;
}

void CPlayer_Draw(CPlayer* Player)
{
	pd->graphics->drawBitmap(Player->Shadow, Player->X + 1, Player->Y + 26, kBitmapUnflipped);
	DrawBitmapSrcRec(Player->Image, Player->X, Player->Y, Player->AnimPhase * Player->Width, 0, Player->Width, Player->Height, kBitmapUnflipped);
}

int CPlayer_GetX(CPlayer* Player)
{
	return Player->X;
}

int CPlayer_GetY(CPlayer* Player)
{
	return Player->Y;
}

int CPlayer_GetWidth(CPlayer* Player)
{
	return Player->Width;
}

void CPlayer_Destroy(CPlayer* Player)
{
 	pd->graphics->freeBitmap(Player->Shadow);
 	pd->graphics->freeBitmap(Player->Image);
	pd->system->realloc(Player, 0);
}

void CPlayer_Move(CPlayer* Player)
{

	if ((Player->State == Walking) || (Player->State==Waiting))
	{
		if (currButtons & kButtonLeft)
		{
			if(Player->X - 2 >= Player->MinX)
			{
				Player->X = Player->X -2;
				Player->AnimPhase = AnimLeft[Player->AnimCounter];
				Player->State = Walking;
			}
			else
				Player->State = Waiting;
		}
 		else
			if (currButtons & kButtonRight)
			{
				if(Player->X + 2 <= Player->MaxX)
				{
					Player->X = Player->X +2;
					Player->AnimPhase = AnimRight[Player->AnimCounter];
					Player->State = Walking;
				}
				else
					Player->State = Waiting;
			}
			else
				Player->State = Waiting;
	}
	if (Player->State == Walking)
	{
		if (Player->Delay > 0)
			Player->Delay--;
		if (Player->Delay == 0)
		{
			Player->AnimCounter++;
			Player->Delay = 3;
		}
     	if (Player->AnimCounter > 5)
     		Player->AnimCounter = 0;
    }
  	if (Player->State == EnterBuilding)
  	{
  		Player->Delay--;
  		if(Player->Delay==0)
  		{
  			Player->AnimCounter++;
  			Player->Y = Player->Y - 1;
  			Player->Delay = 3;
  		}
  		if (Player->AnimCounter > 3)
  		{
  			Player->AnimCounter = 0;
			if(Player->Y <=160)
				Player->State = EnteredBuilding;
		}
 		Player->AnimPhase = AnimEnterBuilding[Player->AnimCounter];
	}
	if (Player->State == Waiting)
	{
		if ((Player->AnimPhase != 0) && (Player->AnimPhase !=13))
		{
			if (Player->AnimPhase==14)
			{
				Player->AnimPhase = 0;
			}
			else
			{
				if (Player->AnimPhase < 7)
					Player->AnimPhase = 0;
				else
					Player->AnimPhase=13;
			}
		}
	}
 	if (Player->State ==LookingUp)
 		Player->AnimPhase = 14;
}
