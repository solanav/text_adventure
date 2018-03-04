
#include "set.h"

#define MAX_INV_SIZE 1024

struct _Set
{
	/* "top" points to next empty space */
	Id id_list[MAX_INV_SIZE];
	int id_total;
};

Set * set_create(int inv_size)
{
	int i;
	Set * set;

	set = (Set *) calloc(1, sizeof(Set));
	if (!set) return NULL;

	for (i=0; i<inv_size; i++)
	{
		set->id_list[i] = NO_ID;
	}

	set->id_total = inv_size;

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
	int i, done;

	for (i=0, done=0; i<set->id_total && done==0; i++)
	{
		if (set->id_list[i] == -1)
		{
			set->id_list[i] = id;
			done++;
		}
	}

	return OK;
}

Id set_pick(Set * set, int num)
{
	Id id_picked;
	
	if (!set) return NO_ID;
	if (num > set->id_total) return NO_ID;
	
	id_picked = set->id_list[num];
	set->id_list[num] = NO_ID;

	return id_picked;
}

Id set_get_id(Set * set, int num)
{
	if (!set) return NO_ID;
	if (num > set->id_total) return NO_ID;

	return set->id_list[num];
}

STATUS set_rm_all(Set * set)
{
	int i=0;

	if (!set) return ERROR;
	
	for (i=0; i<set->id_total; i++)
	{
		set->id_list[i] = -1;
	}

	return OK;
}

Set * set_cp_all(Set * set)
{
	Set * set_copy = set_create(set->id_total);

	

	if (!set) return NULL;
	return NULL;
}

STATUS set_rearrange(Set * set)
{
	if (!set) return ERROR;
	return ERROR;
}

STATUS set_print_debug(FILE * f, Set * set)
{
	int i;

	if (!set) return ERROR;
	
	printf("INV SIZE IS -> %d\n\n", set->id_total);

	for (i=0; i<set->id_total; i++)
	{
		fprintf(f, "POSITION > %d || ID > %ld\n", i, set_get_id(set, i));
	}

	return OK;
}
