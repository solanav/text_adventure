#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "game.h"

typedef struct _Set Set;

Set * set_create();
void set_destroy(Set *);

STATUS set_add(Set *, Id);
Id set_pick(Set *);

Id set_get_id(Set *, int);

STATUS set_print_debug(FILE *, Set *);

#endif
