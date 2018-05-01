/**
 * @brief Low level stack and queue functions
 *
 * @file set.h
 * @author Bernardo Zambrano
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define MAX_INV_SIZE 1024

typedef struct _Set Set;
/**
 *	 @author Pablo Sánchez
 *  @brief esta funcion se encarga de crear el conjunto reservando memoria para el mismo.
 *   @return newset, el inventario creado, o NULL si algo no ha salido como esperaba.
 */
Set * set_create(int);

/**
 *	@author Pablo Sánchez
 * 	@brief esta funcion se encarga de destruir el conjunto.
 *	@param1 el conjunto a destruir.
 */
void set_destroy(Set *);

size_t set_size();

/**
 *	@author Pablo Sánchez
 * 	@brief esta funcion se encarga de añadir un elemento al conjunto.
 *	@param1 el conjunto donde se desea añadir el elemento.
 *	@param2 el id del elemento.
 */
STATUS set_add(Set *, Id);

/**
 *	@author Pablo Sánchez
 * 	@brief esta funcion se encarga de añadir un elemento al conjunto.
 *	@param1 el conjunto donde se desea añadir el elemento.
 *	@param2 el id del elemento.
 */
STATUS set_del(Set *, Id);

/**
 *	@author Antonio Solana
 * 	@brief esta funcion se encarga de obtener el id de un conjunto.
 *	@param1 el conjunto del cual se desea obtener la id
 *  @return devuelve el id del conjunto.
 */
Id set_get_id(Set *, int);

/**
 *	@author Antonio Solana
 * 	@brief esta funcion se encarga de vaciar el set, sin destruirlo
 *	@param1 el set
 *  @return OK o ERROR
 */
STATUS set_rm_all(Set *);

/**
 *  @author Antonio Solana
 *  @brief limpia el set para que no haya espacios vacíos entre los llenos
 *  @param1 el set
 *	@return OK o ERROR
 */
STATUS set_rearrange(Set *);

/**
 *  @author Antonio Solana
 *  @brief copia el set
 *  @param1 el set
 *	@return copia del set
 */
Set * set_cp_all(Set *);

/**
 *  @author Antonio Solana
 *  @brief [DEBUG ONLY] imprime el set dado en el file dado
 *  @param1 el set, un lugar donde imprimir (debe estar abierto)
 *	@return OK o ERROR
 */
STATUS set_print_debug(FILE *, Set *);

 #endif
