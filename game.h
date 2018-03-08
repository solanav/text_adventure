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
#include "set.h"

typedef struct _Game{
  Player * player;
  Set * objects;
  Space* spaces[MAX_SPACES + 1];
  F_Command last_cmd;
} Game;

STATUS game_create(Game* game);
STATUS game_create_from_file(Game* game, char* filename);

STATUS game_update(Game* game, T_Command cmd);
STATUS game_destroy(Game* game);

BOOL   game_is_over(Game* game);

void   game_print_screen(Game* game);
void   game_print_data(Game* game);

Space* game_get_space(Game* game, Id id);
Id  game_get_player_location(Game* game);
Set *  game_get_object_location(Game* game);
F_Command * game_get_last_command(Game* game);
#endif
