#ifndef GAMECOMMON_H
#define GAMECOMMON_H

void CreateGameMenuItems();
void DestroyMenuItems();
void CreateOtherMenuItems();
void DrawPlayField();
void DrawPanel();
int GetLevel(char *Password);
void SaveSettings();
void LoadSettings();
void UnloadImages();
void LoadImages();
#endif