/**
 * @brief Module for player's inventory
 *
 * @file inventory.h
 * @author Guillermo Ríos
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "../include/types.h"
#include "../include/set.h"

typedef struct _Inventory Inventory;

Inventory * inventory_create(int);
STATUS inventory_destroy(Inventory *inv);

STATUS inventory_set_ids(Inventory *inv, Set *ids);
Set * inventory_get_ids(Inventory *inv);

Id inventory_get_id_at(Inventory *inv, int num);

STATUS inventory_add_id(Inventory *inv, Id id);
STATUS inventory_del_id(Inventory *inv, Id id);
BOOL inventory_checkById(Inventory *inv, Id id);

void inventory_print(Inventory *);

#endif
