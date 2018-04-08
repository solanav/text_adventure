#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

Inventory * inventory_create(int);
STATUS inventory_destroy(Inventory *inv);

BOOL inventory_is_full(Inventory *inv);
BOOL inventory_is_empty(Inventory *inv);

STATUS inventory_set_ids(Inventory *inv, Set *ids);
Set * inventory_get_ids(Inventory *inv);

Id inventory_get_id_at(Inventory *inv, int num);

STATUS inventory_set_max(Inventory *inv, int max);
int inventory_get_max(Inventory *inv);

STATUS inventory_add_id(Inventory *inv, Id id);
STATUS inventory_del_id(Inventory *inv, Id id);

void inventory_print(Inventory *);

#endif