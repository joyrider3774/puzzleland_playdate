#ifndef COMMONVARS_H
#define COMMONVARS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "gameobjects/chand.h"
#include "gameobjects/cfairy.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

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

#define GSDeinitDiff 100

#define GSTitleScreenDeInit (GSTitleScreen + GSDeinitDiff)
#define GSOldManSpeakingDeInit (GSOldManSpeaking + GSDeinitDiff) 
#define GSPasswordEntryDeInit (GSPasswordEntry + GSDeinitDiff)
#define GSOptionsDeInit (GSOptions + GSDeinitDiff)
#define GSCreditsDeInit (GSCredits + GSDeinitDiff)
#define GSIntroDeInit (GSIntro + GSDeinitDiff)
#define GSGameDeInit (GSGame + GSDeinitDiff)
#define GSStageClearDeInit (GSStageClear + GSDeinitDiff)
#define GSNextStageDeInit (GSNextStage + GSDeinitDiff)
#define GSStageSelectDeInit (GSStageSelect + GSDeinitDiff)


#define NROFSOUNDS 10
#define SND_RotateBlock 0
#define SND_DropBlock 1
#define SND_FlipBlock 2
#define SND_PickupBlock 3
#define SND_Error 4
#define SND_Menu 5
#define SND_Select 6
#define SND_Bridge 7
#define SND_StageEnd 8
#define SND_Elf 9

#define NROFMUSIC 5
#define MUS_Title 0
#define MUS_Game1 1
#define MUS_Game2 2
#define MUS_Oldman 3
#define MUS_Stage 4

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
extern SDL_Surface* Screen;
extern SDL_Event Event;
extern SDL_Surface* Background;
extern SDL_Surface* Text;
extern CFairy* Fairy;
extern TTF_Font* font;

//Game Stuff
extern int GameState;
extern int Level;
extern CHand* Hand;
extern time_t StartTime,EndTime;
extern Uint32 OldTime;

//Audio
extern bool GlobalSoundEnabled;
extern bool SoundEnabled,MusicEnabled;
extern Mix_Chunk* Sounds[NROFSOUNDS];
extern Mix_Music* Music[NROFMUSIC];

//Puzzle Game Stuff
extern SDL_Surface *BlockImages[BlockCount];
extern SDL_Surface *BorderImages[BorderCount];
extern int PlayField[2][Cols][Rows];
extern bool BlockActive;

//stage Clear Stuff
extern SDL_Surface *RoomBackground,*StageClearKader;

//Next Stage Stuff
extern SDL_Surface *Bridge;
extern SDL_Surface* PrevLevel;
extern SDL_Surface* NextLevel;

#endif