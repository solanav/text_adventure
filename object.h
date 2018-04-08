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
Object* object_create(char* name, Id id);
void object_destroy(Object* obj);

/*
 * Changing the values of the Object
 */
STATUS object_set_name(Object* obj, char* name);
STATUS object_set_id(Object* obj, Id id);
STATUS object_set_description(Object * obj, char * descript);

/*
 * For accesing the object's name and Id
 */
char * object_get_name(Object* obj);
Id object_get_id(Object* obj);
char * object_get_descripton(Object * obj);

#endif
