/**
 * @brief It declares the die module
 *
 * @file die.h
 * @author Pablo Sánchez Redondo
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/types.h"

typedef struct _Die Die;
Die* die_ini(Id);
void die_die_die(Die* );
STATUS die_roll(Die* );
short int die_get_last_roll(Die*);
STATUS die_print(FILE* , Die* );

#endif
