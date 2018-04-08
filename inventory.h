
#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "set.h"
#include "player.h"

typedef struct _Inventory Inventory;
/*  @brief esta funcion se encarga de crear el inventario reservando memoria para el mismo.
	Establece el número máximo de objetos que puede tener.
    @return newinv, el inventario creado, o NULL si algo no ha salido como esperaba.
*/
Inventory * inventory_create(int);
/*  @brief esta funcion se encarga de destruir el inventario.
    @param1 Inventory*, puntero inv al inventario a eliminar.
    @return OK, o ERROR si algo no ha salido como esperaba.
*/
STATUS inentory_destroy(Inventory*);
/*  @brief esta funcion se encarga de añadir un objeto al conjunto que forma el inventario.
    @param1 Inventory*, puntero inv al inventario.
    @return OK, o ERROR si algo no ha salido como esperaba.
*/
STATUS inventory_set_add(Inventory*, Id);
/*  @brief esta funcion se encarga de eliminar un objeto del conjunto que forma el inventario.
    @param1 Inventory*, puntero inv al inventario.
    @return OK, o ERROR si algo no ha salido como esperaba.
*/
STATUS inventory_set_del(Inventory*, Id);
/*  @brief esta funcion se encarga de crear el dado reservando memoria para el mismo.
    @param1 Inventory*, puntero inv al inventario.
	@param2 FILE*, puntero a file donde se imprimirá el conjunto del inventario.
    @return OK, o ERROR si algo no ha salido como esperaba.
*/
STATUS inventory_print(Inventory*,FILE*);

#endif
