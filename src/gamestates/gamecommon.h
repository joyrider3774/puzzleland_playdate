#ifndef GAMECOMMON_H
#define GAMECOMMON_H

void DrawPlayField();
void DrawPanel();
int GetLevel(char *Password);
void WriteText(SDL_Surface* Surface,TTF_Font* FontIn,char* Tekst,int NrOfChars,int X,int Y,int YSpacing,SDL_Color ColorIn);
void SaveSettings();
void LoadSettings();
void UnloadMusic();
void LoadMusic();
void LoadSounds();
void UnloadSounds();
void UnloadImages();
void LoadImages();
#endif