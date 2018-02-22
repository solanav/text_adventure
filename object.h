#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct _Object Object;

/*
 * Functions that, respectively iniciate and free the memory necessary
 * for an Object
 */
Object* obj_create(char* name, Id id);
void obj_destroy(Object* obj);

/*
 * Changing the values of the Object
 */
Object* obj_setName(Object* obj, char* name);
Object* obj_setId(Object* obj, Id id);

/*
 * For accesing the object's name and Id
 */
char* obj_getName(Object* obj);
Id obj_getId(Object* obj);

#endif
