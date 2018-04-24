/**
 * @brief Module for player's inventory
 *
 * @file inventory.c
 * @author Guillermo Ríos
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/inventory.h"

struct _Inventory
{
	Set * ids; /*!< Inventario*/
	int id_max; /*!< Maximo de lugares*/
};

Inventory * inventory_create(int size)
{
	Inventory * inv = NULL;

	inv = (Inventory *)calloc(1, sizeof(Inventory));
	if(!inv) return NULL;

	inv->ids = set_create(size);
	inv->id_max = size;

	return inv;
}

STATUS inventory_destroy(Inventory *inv)
{
	if(!inv) return ERROR;

	set_destroy(inv->ids);

	free(inv);

	return OK;
}

STATUS inventory_setIds(Inventory *inv, Set *ids)
{
	if(!inv || !ids) return ERROR;

	inv->ids = ids;

	return OK;
}

Set * inventory_getIds(Inventory *inv)
{
	if(!inv) return NULL;

	return inv->ids;
}

Id inventory_getIdAt(Inventory *inv, int num)
{
	if(!inv) return NO_ID;

	return set_getId(inv->ids, num);
}

STATUS inventory_setIdMax(Inventory *inv, int id_max)
{
	if(!inv || id_max <= 0) return ERROR;

	inv->id_max = id_max;

	return OK;
}

int inventory_getIdMax(Inventory *inv)
{
	if(!inv) return 0;

	return inv->id_max;
}

STATUS inventory_addId(Inventory *inv, Id id)
{
	if(!inv || id == NO_ID) return ERROR;

	if(set_add(inv->ids, id) == ERROR) return ERROR;

	return OK;
}

STATUS inventory_delId(Inventory *inv, Id id)
{
	if(!inv || id == NO_ID) return ERROR;

	if(set_del(inv->ids, id) == ERROR) return ERROR;

	return OK;
}

void inventory_print(Inventory * inv)
{
	set_printDebug(stdin, inv->ids);
}
