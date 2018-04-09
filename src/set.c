#include "../hdr/set.h"

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
		if (set->id_list[i] == NO_ID)
		{
			set->id_list[i] = id;
			done++;
		}
	}

	return OK;
}

STATUS set_del(Set * set, Id id)
{
	int i;

	if (!set) return ERROR;

	for(i=0; i<set->id_total; i++)
	{
		if(set->id_list[i] == id)
		{
			set->id_list[i] = NO_ID;
			if (set_rearrange(set) == ERROR) return ERROR;
			return OK;
		}
	}

	return ERROR;
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
		set->id_list[i] = NO_ID;
	}

	return OK;
}

Set * set_cp_all(Set * set)
{
	int i;
	Set * set_copy = set_create(set->id_total);

	if (!set) return NULL;

	for (i=0; i<set->id_total; i++)
	{
		set_copy->id_list[i] = set->id_list[i];
	}

	return set_copy;
}

STATUS set_rearrange(Set * set)
{
	/* Moves all ids to fill empty spaces */

	int i, j, removed_count=0;

	if (!set) return ERROR;

	for (i=0, j=0; i<set->id_total; i++)
	{
		if (set->id_list[i] != NO_ID)
		{
			set->id_list[j] = set->id_list[i];
			j++;
		}
		else
		{
			removed_count++;
		}
	}

	for (i=(set->id_total)-1, j=0; j<removed_count; j++, i--)
	{
		set->id_list[i] = NO_ID;
	}

	return OK;
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
