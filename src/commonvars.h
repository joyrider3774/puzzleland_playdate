#ifndef COMMONVARS_H
#define COMMONVARS_H

#include <pd_api.h>
#include <stdbool.h>
#include "gameobjects/chand.h"
#include "gameobjects/cfairy.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240
#define FRAMERATE 30

#define ShowFpsDefault false
#define BatteryMonitoring false

#define GSTitleScreen 1 
#define GSOldManSpeaking 2 
#define GSPasswordEntry 3 
#define GSOptions 4 
#define GSCredits 5 
#define GSIntro 6 
#define GSQuit 7
#define GSGame 8 
#define GSStageClear 9 
#define GSNextStage 10 
#define GSStageSelect 11

#define GSInitDiff 50

#define GSTitleScreenInit (GSTitleScreen + GSInitDiff)
#define GSOldManSpeakingInit (GSOldManSpeaking + GSInitDiff) 
#define GSPasswordEntryInit (GSPasswordEntry + GSInitDiff)
#define GSOptionsInit (GSOptions + GSInitDiff)
#define GSCreditsInit (GSCredits + GSInitDiff)
#define GSIntroInit (GSIntro + GSInitDiff)
#define GSGameInit (GSGame + GSInitDiff)
#define GSStageClearInit (GSStageClear + GSInitDiff)
#define GSNextStageInit (GSNextStage + GSInitDiff)
#define GSStageSelectInit (GSStageSelect + GSInitDiff)

#define BlockCount 13
#define BorderCount 7
#define BlockWidth 12
#define BlockHeight 12
#define XOffsetGame 40
#define YOffsetGame 34
#define XOffsetPassword 50
#define YOffsetPassword 75
#define XOffsetStageSelect 50
#define YOffsetStageSelect 40
#define Cols 20
#define Rows 16
#define MinPlayAreaX XOffsetGame
#define MinPlayAreaY YOffsetGame
#define MaxPlayAreaX (XOffsetGame + BlockWidth * Cols)
#define MaxPlayAreaY (YOffsetGame + BlockHeight * Rows)
#define LetterRows 4
#define LetterCols 7



extern const char* const LevelPasswords[36];
extern const char Letters[4][7];

//common stuff
extern LCDBitmap* Screen;
extern LCDBitmap* Background;
extern LCDBitmap* Text;
extern CFairy* Fairy;
extern LCDFont* font;

//Game Stuff
extern int GameState;
extern int Level;
extern CHand* Hand;
extern unsigned int StartTime,EndTime;
extern uint32_t OldTime;
extern int GameMoveCoolDown, PasswordEntryCoolDown;

//Puzzle Game Stuff
extern LCDBitmap* BlockImages[BlockCount];
extern LCDBitmap *BorderImages[BorderCount];
extern int PlayField[2][Cols][Rows];
extern bool BlockActive;

//stage Clear Stuff
extern LCDBitmap*RoomBackground,*StageClearKader;

//Next Stage Stuff
extern LCDBitmap*Bridge;
extern LCDBitmap* PrevLevel;
extern LCDBitmap* NextLevel;

extern PlaydateAPI* pd;
extern PDButtons currButtons, prevButtons;
extern int showFps;
extern unsigned int prevLogTime;
extern unsigned int FrameTime, Frames;
extern float CurrentMs;

extern LCDFont* Nano, * Mini, * Mini2X;

void setPDPtr(PlaydateAPI* p);
#endif