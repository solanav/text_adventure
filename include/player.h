/**
 * @brief Functions for the creation of players
 *
 * @file player.h
 * @author Guillermo Ríos
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"

typedef struct _Player Player;

/*
 * Inicialize and free the Player module
 */
Player * player_create(char *, Id, Id, Id);
void player_destroy(Player *);

/*
 * Changing each singular value of the Player
 */
STATUS player_setName(Player *, char *);
STATUS player_setLocId(Player *, Id);
STATUS player_setObjId(Player *, Id);
STATUS player_setId(Player *, Id);

/*
 * Access the Player's values
 */
char * player_getName(Player *);
Id player_getLocId(Player *);
Id player_getObjId(Player *, int);
Id player_getId(Player *);

STATUS player_removeObjId(Player *, Id);

#endif
