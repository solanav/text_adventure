/**
 * @brief Defines functions for space manipulation
 *
 * @file space.h
 * @author Catalín Rotaru
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "../include/types.h"
#include "../include/object.h"
#include "../include/set.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

Space *space_create(Id id);
STATUS space_destroy(Space *space);

Id space_get_id(Space *space);

STATUS space_set_name(Space *space, char *name);
const char *space_get_name(Space *space);

STATUS space_set_description(Space *space, char *description);
const char *space_get_description(Space *space);
/**
 * @author Pablo Sánchez
 * @brief esta funcion se encarga de modificar el id de la cordenada "norte".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/

STATUS space_set_north(Space *space, Id id);
/**
 * @author Pablo Sanchez
 * @brief esta funcion se encarga de obtener el id de la cordenada "norte".
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_north(Space *space);
/**
 * @author Pablo Sánchez
 * @brief esta funcion se encarga de modificar el id de la cordenada "sur".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/

STATUS space_set_south(Space *space, Id id);
/**
 * @author Pablo Sanchez
 * @brief esta funcion se encarga de obtener el id de la cordenada "sur".
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_south(Space *space);
/**
 * @author Pablo Sánchez
 * @brief esta funcion se encarga de modificar el id de la cordenada "este".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/

STATUS space_set_east(Space *space, Id id);
/**
 * @author Pablo Sanchez
 * @brief esta funcion se encarga de obtener el id de la cordenada "este".
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_east(Space *space);
/**
 * @author Pablo Sánchez
 * @brief esta funcion se encarga de modificar el id de la cordenada "oeste".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/

STATUS space_set_west(Space *space, Id id);

/**
 * @author Pablo Sanchez
 * @brief esta funcion se encarga de obtener el id de la cordenada del oeste.
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_west(Space *space);

/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion se encarga de modificar el id de la cordenada "arriba".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/
STATUS space_set_up(Space *space, Id id);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion se encarga de obtener el id de la cordenada "arriba".
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_up(Space *space);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion se encarga de modificar el id de la cordenada "abajo".
 * @param1 el espacio a modificar.
 * @param2 el nuevo id.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/
STATUS space_set_down(Space *space, Id id);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion se encarga de obtener el id de la cordenada "abajo".
 * @param1 el espacio a obtener la id.
 * @return devuelve la id del espacio o NO_ID si hubo algun error.
*/
Id space_get_down(Space *space);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion se encarga de modificar la iluminacion de un espacio dado.
 * @param1 el espacio a modificar
 * @param2 la iluminacion que se desea poner.
 * @return devuelve OK si todo salio correctamente o ERROR si no.
*/
STATUS space_set_light(Space *space, BOOL light);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion devuelve la iluminacion de un espacio dado.
 * @param1 el espacio a modificar
 * @return devuelve TRUE si el espacio esta iluminado o FALSE si no lo esta o no existe.
*/
BOOL space_get_light(Space *space);

STATUS space_add_object(Space *space, Id obj_id);
STATUS space_remove_object(Space *space, Id obj_id);
Set *space_get_objects_id(Space *space);

STATUS space_set_gdesc_0(Space *, char *);
STATUS space_set_gdesc_1(Space *, char *);
STATUS space_set_gdesc_2(Space *, char *);

char *space_get_gdesc_0(Space *);
char *space_get_gdesc_1(Space *);
char *space_get_gdesc_2(Space *);
/**
 * @author Bernardo Zambrano Guillermo Rios
 * @brief esta funcion muestra por pantalla el espacio, y los objetos que estan en el dependiendo de la iluminacion del mismo.
 * @param1 el espacio a mostrar.
 * @return devuelve OK si se imprimio correctamente o ERROR si algo no ha salido bien.
*/
STATUS space_light_print(Space *space);
STATUS space_print(Space *space);

/**
*	@author: Antonio Solana
*	@brief: Saca la linea deseada del sprite
*	@param: Space
*	@param: numero de la linea
*	@return: el Id en la posicion
*/
Id space_getSprite(Space *, int);

/**
*	@author: Antonio Solana
*	@brief: Mete la linea deseada en el sprite
*	@param: Space
*	@param: string a meter
*	@param: numero de la linea
*	@return: STATUS
*/
STATUS space_setSprite(Space *, Id, int);

/**
*	@author: Antonio Solana
*	@brief: Set para la sprite que deberia estar usandose
*	@param: Space
*	@param: numero de la sprite
*	@return: STATUS
*/
STATUS space_setCurrentSprite(Space *space, int i);

/**
*	@author: Antonio Solana
*	@brief: Get para la sprite en uso actualmente
*	@param: Space
*	@return: STATUS
*/
int space_getCurentSprite(Space *space);

#endif
