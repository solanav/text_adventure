/**
 * @brief Defines functions for space manipulation
 *
 * @file space.h
 * @author Catalín Rotaru
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "../include/types.h"
#include "../include/object.h"
#include "../include/set.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

Space* 		space_create(Id id);
STATUS 		space_destroy(Space* space);

Id 			space_getId(Space* space);

STATUS 		space_setName(Space* space, char* name);
const char* space_getName(Space* space);

STATUS		space_setDescription(Space* space, char* description);
const char* space_getDescription(Space* space);

STATUS 		space_setNorth(Space* space, Id id);
Id 			space_getNorth(Space* space);

STATUS 		space_setSouth(Space* space, Id id);
Id 			space_getSouth(Space* space);

STATUS 		space_setEast(Space* space, Id id);
Id 			space_getEast(Space* space);

STATUS 		space_setWest(Space* space, Id id);
Id 			space_getWest(Space* space);

STATUS 		space_addObject(Space* space, Id obj_id);
STATUS 		space_removeObject(Space* space, Id obj_id);
Set * 		space_getObjectsId(Space* space);

STATUS		space_setGdesc0(Space *, char *);
STATUS		space_setGdesc1(Space *, char *);
STATUS		space_setGdesc2(Space *, char *);

char *		space_getGdesc0(Space *);
char *		space_getGdesc1(Space *);
char *		space_getGdesc2(Space *);

STATUS space_print(Space* space);

#endif
