
#include "set.h"

#define INV_SIZE 1024

struct _Set
{
	/* "top" points to next empty space */
	Id id_list[INV_SIZE];
	int top;
};

Set * set_create()
{
	int i;
	Set * set;

	set = (Set *) calloc(1, sizeof(Set));
	if (!set) return NULL;

	for (i=0; i<INV_SIZE; i++)
	{
		set->id_list[i] = NO_ID;
	}

	set->top = 0;

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
	set->id_list[set->top] = id;
	set->top++;

	return OK;
}

Id set_pick(Set * set)
{
	set->top--;
	Id id_picked = set->id_list[set->top];
	set->id_list[set->top] = NO_ID;

	return id_picked;
}

Id set_get_id(Set * set, int i)
{
	return set->id_list[i];	
}

STATUS set_print_debug(FILE * f, Set * set)
{
	int i;

	if (!set) return ERROR;
	
	for (i=(set->top)-1; i>=0; i--)
	{
		fprintf(f, "POSITION > %d || ID > %ld\n", i, set_get_id(set, i));
	}

	return OK;
}
