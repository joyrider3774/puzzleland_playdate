#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void MoveBlockRight();
void MoveBlockLeft();
void MoveBlockUp();
void MoveBlockDown();
void MakeBlockActive(const int X,const int Y,const int BlockNr);
bool MakeBlockUnActive();
void FlipBlock(const bool Horizontal);
void RotateBlock();
void DrawPlayField();
void LoadLevel();
bool IsStageClear();
void DrawPanel();
void Game();
void GameDeInit();

#endif