#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct _Set Set;

Set * set_create(int);
void set_destroy(Set *);

STATUS set_add(Set *, Id);
STATUS set_del(Set *, Id);
Id set_get_id(Set *, int);

STATUS set_rm_all(Set *);
STATUS set_rearrange(Set *);
Set * set_cp_all(Set *);

STATUS set_print_debug(FILE *, Set *);

#endif
