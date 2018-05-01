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

size_t space_size();

Id 			space_get_id(Space* space);

STATUS 		space_set_name(Space* space, char* name);
const char* space_get_name(Space* space);

STATUS		space_set_description(Space* space, char* description);
const char* space_get_description(Space* space);

STATUS 		space_set_north(Space* space, Id id);
Id 			space_get_north(Space* space);

STATUS 		space_set_south(Space* space, Id id);
Id 			space_get_south(Space* space);

STATUS 		space_set_east(Space* space, Id id);
Id 			space_get_east(Space* space);

STATUS 		space_set_west(Space* space, Id id);
Id 			space_get_west(Space* space);

STATUS 		space_add_object(Space* space, Id obj_id);
STATUS 		space_remove_object(Space* space, Id obj_id);
Set * 		space_get_objects_id(Space* space);
STATUS		space_set_objects_id(Space* space, Set* ids);

STATUS		space_set_gdesc_0(Space *, char *);
STATUS		space_set_gdesc_1(Space *, char *);
STATUS		space_set_gdesc_2(Space *, char *);

char *		space_get_gdesc_0(Space *);
char *		space_get_gdesc_1(Space *);
char *		space_get_gdesc_2(Space *);

STATUS space_print(Space* space);

#endif
