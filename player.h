#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct _Player Player;

/*
 * Inicialize and free the Player module
 */
Player * player_create(char * name, Id location_id, Id object_id, Id id);
Player * player_destroy(Player * player);

/*
 * Changing each singular value of the Player
 */
Player * player_setName(Player * player, char * newName);
Player * player_setLocId(Player * player, Id new_locId);
Player * player_setObjId(Player * player, Id new_objId);
Player * player_setId(Player * player, Id new_id);

/*
 * Access the Player's values
 */
char * player_getName(Player * player);
Id player_getLocId(Player * player);
Id player_getObjId(Player * player);
Id player_getId(Player * player);


#endif
