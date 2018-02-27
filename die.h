#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

typedef struct _Die Die;

/*This functions create and destroy (respectively) one Die for the game*/
Die* die_ini(Id);
void die_die_die(Die* );

/*Rolls the dice and returns the result*/
int die_roll(Die* );

/*Prints  Dice Id and result*/
STATUS die_print(FILE* , Die* );

#endif
