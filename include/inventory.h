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

STATUS inventory_setIds(Inventory *inv, Set *ids);
Set * inventory_getIds(Inventory *inv);

Id inventory_getIdAt(Inventory *inv, int num);


STATUS inventory_setIdMax(Inventory *inv, int id_max);
int inventory_getIdMax(Inventory *inv);

STATUS inventory_addId(Inventory *inv, Id id);
STATUS inventory_delId(Inventory *inv, Id id);

void inventory_print(Inventory *);

#endif
