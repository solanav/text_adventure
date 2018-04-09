/**
 * @brief Commands and user input
 * 
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "../hdr/types.h"

typedef struct _Object Object;

Object* object_create(char *, Id);
void object_destroy(Object *);

STATUS object_set_name(Object *, char *);
STATUS object_set_id(Object *, Id);
STATUS object_set_description(Object *, char *);

char * object_get_name(Object* obj);
char * object_get_description(Object* obj);
Id object_get_id(Object* obj);

#endif
