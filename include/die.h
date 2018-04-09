/**
 * @brief Commands and user input
 *
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/types.h"

typedef struct _Die Die;

/*This functions create and destroy (respectively) one Die for the game*/
Die* die_ini(Id);
void die_die_die(Die* );

/*Rolls the dice and returns the result*/
STATUS die_roll(Die* );
short int die_get_last_roll(Die*);

/*Prints  Dice Id and result*/
STATUS die_print(FILE* , Die* );

#endif
