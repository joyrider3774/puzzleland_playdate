#include <SDL.h>
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
//common stuff
SDL_Surface* Screen;
SDL_Event Event;
SDL_Surface* Background = NULL;
SDL_Surface* Text = NULL;
CFairy* Fairy;
TTF_Font* font;

//Game Stuff
int GameState = GSIntroInit;
int Level;
CHand* Hand;
time_t StartTime,EndTime;
Uint32 OldTime = 0;

//Audio
bool GlobalSoundEnabled = true;
bool SoundEnabled=true,MusicEnabled=true;
Mix_Chunk* Sounds[NROFSOUNDS];
Mix_Music* Music[NROFMUSIC];

//Puzzle Game Stuff
SDL_Surface *BlockImages[BlockCount];
SDL_Surface *BorderImages[BorderCount];
int PlayField[2][Cols][Rows];
bool BlockActive;

//stage Clear Stuff
SDL_Surface *RoomBackground = NULL;
SDL_Surface *StageClearKader = NULL;

//Next Stage Stuff
SDL_Surface *Bridge = NULL;
SDL_Surface* PrevLevel = NULL;
SDL_Surface* NextLevel = NULL;

