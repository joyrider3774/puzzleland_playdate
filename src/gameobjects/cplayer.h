#ifndef CPLAYER_H
#define CPLAYER_H
#include <SDL.h>

typedef enum {Walking,Waiting,LookingUp,EnterBuilding,EnteredBuilding} PlayerStates;

typedef struct CPlayer CPlayer;
struct CPlayer
{
 	PlayerStates State;
 	SDL_Surface *Image,*Shadow;
 	int X,Y,AnimPhase,AnimCounter,Delay,Width,Height,MinX,MaxX;
};

void CPlayer_Move(CPlayer* Player);
void CPlayer_Destroy(CPlayer* Player);
int CPlayer_GetWidth(CPlayer* Player);
int CPlayer_GetY(CPlayer* Player);
int CPlayer_GetX(CPlayer* Player);
void CPlayer_Draw(CPlayer* Player);
CPlayer* CPlayer_Create(const int Xin,const int Yin,const int MinXin, const int MaxXin);
#endif