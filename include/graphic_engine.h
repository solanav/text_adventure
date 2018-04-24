/**
 * @brief Uses screen.* to create the UI
 *
 * @file graphic_engine.h
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "../include/game.h"
#include "../include/screen.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engineCreate();
void graphic_engineDestroy(Graphic_engine *);
void graphic_enginePaintGame(Graphic_engine *, Game *);

/*
	int = 0 -> top space
	int = 1 -> middle space
	int = 2 -> bottom space
*/
void graphic_enginePaintSpace(Graphic_engine *, Game *, int);

char * create_objectsString(Game *, Id);
void print_newLine(Area *, int number);


#endif
