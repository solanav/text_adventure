
#include "set.h"

#define INV_SIZE 1024

struct _Set
{
	/* Cambiar a macro */
	Id id_list[INV_SIZE];
	int id_total;
};

Set * set_create()
{
	int i;
	Set* set;

	/* Borrar set pasado si ya existe? */
	set = (Set *) calloc(1, sizeof(Set));
	if (!set) return NULL;

	for (i=0; i<INV_SIZE; i++)
	{
		set->id_list[i] = -1;
	}

	set->id_total = 0;

	return set;
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

	for (i=0, checker=0; i<INV_SIZE && checker==0; i++)
	{
		if (set->id_list[i] == -1)
		{
			/* When found id without value append new id */
			set->id_list[i] = id;
			checker = 1;
		}
	}
	set->id_total++;
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

	set->id_total--;
	return OK;
}

STATUS set_print(FILE * f, Set * set)
{
	int i;

	if (!set) return ERROR;

	for (i=0; i<=set->id_total; i++)
	{
		if(set->id_list[i]!=-1)
		{
			fprintf(f, "%d -> id: %ld\n", i+1, set->id_list[i]);
		}
	}
	fprintf(f, "Total items in set: %d\n", set->id_total);

	return OK;
}
