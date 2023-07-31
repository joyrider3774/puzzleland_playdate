#include <pd_api.h>
#include <stdbool.h>
#include "commonvars.h"
#include "gameobjects/chand.h"
#include "gameobjects/cfairy.h"

//audio
const char* const LevelPasswords[36] = {"DAVY","DISK","TREE","SEAL",
									 "OPEN","LION","WINE","GROW",
									 "FOOD","DUEL","MEAT","FLEE",
									 "DUST","LOST","HELP","MILK",
									 "SAFE","DULL","SAVE","BEER",
									 "BILL","BLOW","BIKE","VENT",
									 "ROOM","HOOD","MOOD","FEAR",
									 "REEF","POLE","BEEF","SONG",
									 "HOPE","BLUE","MAIL","MONK"};
const char Letters[4][7] = {{'A','B','C','D','E','F','G'},
							  {'H','I','J','K','L','M','N'},
							  {'O','P','Q','R','S','T','U'},
							  {'V','W','X','Y','Z','0','0'}};
PlaydateAPI* pd;
PDButtons currButtons, prevButtons;
unsigned int prevLogTime = 0u;
int showFps = ShowFpsDefault;
int GameMoveCoolDown, PasswordEntryCoolDown;

//common stuff
LCDBitmap* Background = NULL;
LCDBitmap* Text = NULL;
CFairy* Fairy;
LCDFont* Nano, * Mini, * Mini2X;

//Game Stuff
int GameState = GSIntroInit;
int Level;
CHand* Hand;
bool NeedGameReset = false;
unsigned int StartTime,EndTime;
uint32_t OldTime = 0;
PDMenuItem* menuItem1 = NULL, * menuItem2 = NULL, * menuItem3 = NULL;

//Puzzle Game Stuff
LCDBitmap* BlockImages[BlockCount];
LCDBitmap* BorderImages[BorderCount];
int PlayField[2][Cols][Rows];
bool BlockActive;

//stage Clear Stuff
LCDBitmap* RoomBackground = NULL;
LCDBitmap* StageClearKader = NULL;

//Next Stage Stuff
LCDBitmap* Bridge = NULL;
LCDBitmap* PrevLevel = NULL;
LCDBitmap* NextLevel = NULL;

unsigned int FrameTime, Frames;
float CurrentMs;

void setPDPtr(PlaydateAPI* p) {
	pd = p;
}

