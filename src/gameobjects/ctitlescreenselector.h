#ifndef CTITLESCREENSELECTOR_H
#define CTITLESCREENSELECTOR_H

#include <sdl.h>

typedef struct CTitleScreenSelector CTitleScreenSelector;
struct CTitleScreenSelector
{
	int X,Selection;
	SDL_Surface *Image;
};

CTitleScreenSelector* CTitleScreenSelector_Create();
void CTitleScreenSelector_MoveUp(CTitleScreenSelector* selector);
void CTitleScreenSelector_MoveDown(CTitleScreenSelector* selector);
void CTitleScreenSelector_Draw(CTitleScreenSelector* selector);
void CTitleScreenSelector_destroy(CTitleScreenSelector* selector);

#endif