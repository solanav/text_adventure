#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define MAX_INV_SIZE 1024

typedef struct _Set Set;
/*  @brief esta funcion se encarga de crear el conjunto reservando memoria para el mismo.
    @return newset, el inventario creado, o NULL si algo no ha salido como esperaba.
*/
Set * set_create(int);
/*  @brief esta funcion se encarga de destruir el conjunto.
	@param1 el conjunto a destruir.
   
*/
void set_destroy(Set *);
/*  @brief esta funcion se encarga de añadir un elemento al conjunto.
	@param1 el conjunto donde se desea añadir el elemento.
	@param2 el id del elemento.
   
*/

STATUS set_add(Set *, Id);
/*  @brief esta funcion se encarga de añadir un elemento al conjunto.
	@param1 el conjunto donde se desea añadir el elemento.
	@param2 el id del elemento.
    
*/
STATUS set_del(Set *, Id);
/*  @brief esta funcion se encarga de obtener el id de un conjunto.
	@param1 el conjunto del cual se desea obtener la id
    @return devuelve el id del conjunto.
*/
Id set_get_id(Set *, int);
STATUS set_rm_all(Set *);
STATUS set_rearrange(Set *);
Set * set_cp_all(Set *);
STATUS set_print_debug(FILE *, Set *);

#endif
