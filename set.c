#include <stdio.h>
#include <stdlib.>

#include "types.h"

#define INV_SIZE 1024

typedef struct _Set
{
	/* Cambiar a macro */
	Id id_list[INV_SIZE];
	int id_total;
} Set;

Set * set_create()
{
	int i;

	/* Borrar set pasado si ya existe? */
	set = (Set *) calloc(1, sizeof(Set));
	if (!set) return ERROR;
	
	for (i=0; i<INV_SIZE; i++)
	{
		set->id_list[i] = -1;
	}

	set->id_total = 0;

	return OK;
}

void set_destroy(Set * set)
{
	if (!set) return;
	free(set);

	return;
}

STATUS set_add(Set * set, Id id)
{
	int i, checker;

	if (!set) return ERROR;

	for (i=0, checker=0; i<INV_SIZE && checker=0; i++)
	{
		if (set->id_list[i] == -1)
		{
			/* When found id without value append new id */
			set->id_list[i] = id;
			checker = 1;
		}
	}

	return OK;
}

STATUS set_del(Set * set, Id id)
{
	/* Replaces the looked for id with a zero */

	int i;

	if (!set || id == -1) return ERROR;

	for (i=0; i<INV_SIZE; i++)
	{
		if (set->id_list[i] == id)
		{
			set->id_list[i] = -1;
		}
	}
}

STATUS set_print(Set * set)
{
	int i;
	
	if (!set) return ERROR;
	
	for (i=0; i<INV_SIZE; i++)
	{
		obj_p 	 = game_get_object
		obj_id 	 = obj_getId(set->id_list[i]);
		obj_name = obj_getName(set->id_list[i]);

		printf("%d -> %ld [%s]", i, obj_id, obj_name);
	}
}
