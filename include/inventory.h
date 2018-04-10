/**
 * @brief Commands and user input
 *
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
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

void inventory_print(Inventory *);

#endif
