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

Id 		game_getPlayerLocation(Game *);
Id	 	game_getObjectLocation(Game *, Id);
Id		game_getSpaceIdAt(Game *, int);
int		game_getLastRoll(Game *);


STATUS	game_addSpace(Game *, Space *);
STATUS 	game_setPlayerLocation(Game *, Id);
STATUS 	game_setObjectLocation(Game *, Id, Id, char *, char *);
STATUS	game_setLink(Game *, Id, Id, Id);

STATUS	game_loadspaces(Game *, char *);

F_Command*	game_getLastCommand(Game *);
T_Command	game_getLastCommandText(Game *);

BOOL game_areSpacesAdjacent(Game *, Id, Id);

#endif
