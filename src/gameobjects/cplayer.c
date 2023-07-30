#include <SDL.h>
#include <SDL_image.h>
#include "../commonvars.h"
#include "cplayer.h"

//Player anims
const int AnimLeft[6]= {12,11,10,9,8,7};
const int AnimRight[6]  = {1,2,3,4,5,6};
const int AnimEnterBuilding[4]  = {15,16,17,18};


CPlayer* CPlayer_Create(const int Xin,const int Yin,const int MinXin, const int MaxXin)
{
	CPlayer* Result = (CPlayer *) malloc(sizeof(CPlayer));
 	Result->Image = IMG_Load("./graphics/ryf-player.png");
 	Result->Shadow = IMG_Load("./graphics/ryf-shadow.png");
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
	SDL_Rect DstRect,SrcRect;
	DstRect.x = Player->X + 1;
 	DstRect.y = Player->Y + 26;
 	DstRect.w = Player->Shadow->w;
 	DstRect.h = Player->Shadow->h;
 	SDL_BlitSurface(Player->Shadow,NULL,Screen,&DstRect);

 	DstRect.x = Player->X;
 	DstRect.y = Player->Y;
 	DstRect.w = Player->Width;
 	DstRect.h = Player->Height;
 	SrcRect.x = Player->AnimPhase * Player->Width;
 	SrcRect.y = 0;
 	SrcRect.w = Player->Width;
 	SrcRect.h = Player->Height;
	SDL_BlitSurface(Player->Image,&SrcRect,Screen,&DstRect);
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
 	SDL_FreeSurface(Player->Shadow);
 	SDL_FreeSurface(Player->Image);
	free(Player);
}

void CPlayer_Move(CPlayer* Player)
{

	if ((Player->State == Walking) || (Player->State==Waiting))
	{
		Uint8* keyState = SDL_GetKeyState(NULL);
   		if(keyState[SDLK_LEFT])
		{
			if(Player->X - 3 >= Player->MinX)
			{
				Player->X = Player->X -3;
				Player->AnimPhase = AnimLeft[Player->AnimCounter];
				Player->State = Walking;
			}
			else
				Player->State = Waiting;
		}
 		else
			if(keyState[SDLK_RIGHT])
			{
				if(Player->X + 3 <= Player->MaxX)
				{
					Player->X = Player->X +3;
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
     	Player->AnimCounter++;
     	if (Player->AnimCounter > 5)
     		Player->AnimCounter = 0;
    }
  	if (Player->State == EnterBuilding)
  	{
  		Player->Delay++;
  		if(Player->Delay==3)
  		{
  			Player->AnimCounter++;
  			Player->Y = Player->Y - 1;
  			Player->Delay = 0;
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
