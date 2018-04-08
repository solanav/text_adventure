#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"

struct _Inventory
{
  Set *ids;
  int id_max;
};

Inventory * inventory_create(int size)
{
  Inventory *inv = NULL;

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

STATUS inventory_set_ids(Inventory *inv, Set *ids)
{
  if(!inv || !ids) return ERROR;

  inv->ids = ids;

  return OK;

}

Set * inventory_get_ids(Inventory *inv)
{
  if(!inv) return NULL;

  return inv->ids;
}

Id inventory_get_id_at(Inventory *inv, int num)
{
  if(!inv) return NO_ID;

  return set_get_id(inv->ids, num);
}

STATUS inventory_set_id_max(Inventory *inv, int id_max)
{
  if(!inv || id_max <= 0) return ERROR;

  inv->id_max = id_max;

  return OK;
}

int inventory_get_id_max(Inventory *inv)
{
  if(!inv) return 0;

  return inv->id_max;
}

STATUS inventory_add_id(Inventory *inv, Id id)
{
  if(!inv || id == NO_ID) return ERROR;

  if(set_add(inv->ids, id) == ERROR) return ERROR;

  return OK;
}

STATUS inventory_del_id(Inventory *inv, Id id)
{
  if(!inv || id == NO_ID) return ERROR;

  if(set_del(inv->ids, id) == ERROR) return ERROR;

  return OK;
}

void inventory_print(Inventory * inv)
{
	set_print_debug(stdin, inv->ids);
}