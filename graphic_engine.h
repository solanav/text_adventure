/** 
 * @brief It defines a textual graphic engine
 * 
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
#include "screen.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine *);
void graphic_engine_paint_game(Graphic_engine *, Game *);

/* 	
	int = 0 -> up
	int = 1 -> middle
	int = 2 -> down
*/
void graphic_engine_paint_space(Graphic_engine *, Game *, int);

void print_new_line(Area *, int number);
char * create_objects_string(Game *, Id);

#endif
