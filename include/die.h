/**
 * @brief It declares the die module
 *
 * @file die.h
 * @author Pablo Sánchez Redondo
 * @copyright GNU Public License
 */

 #ifndef DIE_H
 #define DIE_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include "types.h"
 /*
     la estructura _Die consta de dos componentes, uno de ellos, ID (donde se guardara el id de los dados) e int ult_tirada
     (donde se guarda el ultimo resultado de la funcion roll_die() ).
 */
 typedef struct _Die Die;
 /*
     @author Pablo Sánchez
     @brief esta funcion se encarga de crear el dado reservando memoria para el mismo.
     @param1 ID, el id del dado.
     @return newdie, el dado creado, o NULL si algo no ha salido como esperaba.
 */
 Die* die_ini(Id);
 /*  @author Pablo Sánchez
     @brief Destruye el dado recibido
	 @param *Die
 */
 void die_die_die(Die* );
 /*  @author Pablo Sánchez
     @brief esta funcion se encarga de llamar a la funcion aleatorio() para simular la tirada del dado y devolver el numero elegido
     @return Die=>ult_tirada si ha salido correctamente o ERROR si no.
 */
 STATUS die_roll(Die* );
 /*  @author Pablo Sánchez
     @brief consigue el valor de la ultima tirada
     @param1 Die*
     @return short int la ultima tirada
 */
 short int die_get_last_roll(Die*);
 /*  @author Pablo Sánchez
     @brief esta funcion se encarga de imprimir el contenido del dado
     @param1 Die*die, el dado que desea imprimir.
     @return ERROR si algo no ha salido como se esperaba.
 */
 STATUS die_print(FILE* , Die* );

 #endif
