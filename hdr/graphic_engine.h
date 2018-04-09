/**
 * @brief Commands and user input
 * 
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "../hdr/game.h"
#include "../hdr/screen.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine *);
void graphic_engine_paint_game(Graphic_engine *, Game *);

/* 	
	int = 0 -> top space
	int = 1 -> middle space
	int = 2 -> bottom space
*/
void graphic_engine_paint_space(Graphic_engine *, Game *, int);

void print_new_line(Area *, int number);
char * create_objects_string(Game *, Id);

#endif
