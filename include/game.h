/**
 * @brief Main function
 *
 * @file game.h
 * @author Bernardo Zambrano
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "../include/command.h"
#include "../include/space.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/die.h"
#include "../include/link.h"
#include "../include/inventory.h"

#define MAX_OBJECTS 4

typedef struct _Game Game;

Game*	game_create();
STATUS 	game_createFromFile(Game *, char *);

STATUS 	game_update(Game *, F_Command *);
STATUS	game_destroy(Game *);

BOOL   	game_isOver(Game *);

void   	game_printScreen(Game *);
void   	game_printData(Game *);

Space*	game_getSpace(Game *, Id);
Player*	game_getPlayer(Game *);
Object* game_getObject(Game *, char *);
Object * game_getObjectFromId(Game * game, Id id);
Link*	game_getLink(Game *, Id);
Id		game_getLinkIdAt(Game *, int);

Id 		game_get_player_location(Game *);
Id	 	game_get_object_location(Game *, Id);
Id		game_get_space_id_at(Game *, int);
Id    game_get_object_id_at(Game *, int);
int		game_get_last_roll(Game *);


STATUS	game_add_space(Game *, Space *);
STATUS 	game_set_player_location(Game *, Id);
STATUS game_set_object(Game *, Object *);
STATUS 	game_set_object_location(Game *, Id, Id);
STATUS	game_set_link(Game *, Id, Id, Id);

STATUS	game_loadspaces(Game *, char *);

F_Command*	game_get_last_command(Game *);
F_Command*  game_get_earlier_command(Game*);
T_Command	game_get_last_command_text(Game *, int);
char *		game_get_last_command_parameters(Game *, int);

BOOL game_areSpacesAdjacent(Game *, Id, Id);

#endif
