/**
 * @brief It defines the game interface
 * for each command
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "object.h"
#include "player.h"
#include "die.h"

#define MAX_OBJECTS 4

typedef struct _Game
{
  Player * player;
  Object * objects[MAX_OBJECTS];
  Space* spaces[MAX_SPACES + 1];
  F_Command * last_cmd;
} Game;

STATUS 	game_create(Game *);
STATUS 	game_create_from_file(Game *, char *);

STATUS 	game_update(Game *, F_Command *);
STATUS	game_destroy(Game *);

BOOL   	game_is_over(Game *);

void   	game_print_screen(Game *);
void   	game_print_data(Game *);

Space * game_get_space(Game *, Id);
Id 		game_get_player_location(Game *);
Id	 	game_get_object_location(Game *, Id);
Id		game_get_space_id_at(Game *, int);

STATUS	game_add_space(Game *, Space *);
STATUS 	game_set_player_location(Game *, Id);
STATUS 	game_set_object_location(Game *, Id, Id);

STATUS	game_load_spaces(Game *, char *);

F_Command * game_get_last_command(Game *);
T_Command 	game_get_last_command_text(Game *);

#endif
