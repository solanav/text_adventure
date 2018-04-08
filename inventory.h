#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"
/*
    la estructura _Inventory consta de dos componentes, uno de ellos, un puntero a set (donde se guardaran los elementos en forma de conjunto) e int num_max_obj
    (donde se guarda el numero de elementos maximos que puede poseer un jugador).
*/
typedef struct _Inventory Inventory;
/*  @author Guillermo Ríos
	@date 23/03/2018
    @brief esta funcion se encarga de crear el inventario.
    @param1 numero entero
    @return newinv si se ha creado correctamente o NULL si no.
*/
Inventory * inventory_create(int);
/*  @author Guillermo Ríos
	@date 23/03/2018
    @brief esta funcion se encarga de destruir el inventario.
    @param1 Inventory*, el inventario a eliminar
    @return OK si se ha liberado correctamente o ERROR si no.
*/
STATUS inventory_destroy(Inventory *inv);
/*  @author 
	@date 06/04/2018
    @brief esta funcion se encarga de comprobar si un inventario esta lleno.
    @param1 Inventory*, el inventario.
    @return TRUE si esta llenoo FALSE si no.
*/
BOOL inventory_is_full(Inventory *inv);
/*  @author 
	@date 06/04/2018
    @brief esta funcion se encarga de comprobar si un inventario esta vacio.
    @param1 Inventory*, el inventario.
    @return TRUE si esta vacio FALSE si no.
*/
BOOL inventory_is_empty(Inventory *inv);
/*  @author 
	@date 04/04/2018
    @brief esta funcion se encarga de editar el id de los conjuntos.
    @param1 Inventory*, el inventario.
	@param2 Set* ids, los ids de los conjuntos
    @return OK si salió como esperaba o ERROR si no.
*/

STATUS inventory_set_ids(Inventory *inv, Set *ids);
/*  @author 
	@date 06/04/2018
    @brief esta funcion se encarga de obtener el id de los elementos del conjunto.
    @param1 Inventory*, el inventario.
    @return el id del conjunto.
*/
Set * inventory_get_ids(Inventory *inv);
Id inventory_get_id_at(Inventory *inv, int num);
/*  @author 
	@date 21/03/2018
    @brief esta funcion se encarga de establecer el maximo de objetos
    @param1 Inventory*, el inventario.
	@param2 int, numero entero de objetos máximos que se desea establecer
    @return TOK si todo salio correctamente o ERRROR si no.
*/

STATUS inventory_set_max(Inventory *inv, int max);
/*  @author 
	@date 21/03/2018
    @brief esta funcion se encarga de obtener el maximo de objetos
    @param1 Inventory*, el inventario.
    @return el numer maximo de objetos establecido.
*/

int inventory_get_max(Inventory *inv);
/*  @author Guillermo Rios
	@date 03/04/2018
    @brief esta funcion se encarga de añadir un objeto al inventario.
    @param1 Inventory*, el inventario.
	@param2 el id del objeto que se desea añadir.
    @return OK si se añadió correctamente o ERROR si no.
*/

STATUS inventory_add_id(Inventory *inv, Id id);
/*  @author Guillermo Rios
	@date 03/04/2018
    @brief esta funcion se encarga de eliminar un objeto al inventario.
    @param1 Inventory*, el inventario.
	@param2 el id del objeto que se desea eliminar.
    @return OK si se eliminó correctamente o ERROR si no.
*/
STATUS inventory_del_id(Inventory *inv, Id id);
/*  @author Guillermo Rios
	@date 06/04/2018
    @brief esta funcion se encarga de imprimir el contenido del inventario
    @param1 Inventory*, el inventario.
*/

void inventory_print(Inventory *);

#endif