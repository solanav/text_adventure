#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/*  En este caso cada jugador tendrá una id
   -Con un nombre de máximo de caracteres [WORD_SIZE+1] .
   -Con un id de espacio
   -Y por último un id donde posee el objeto
*/
typedef struct _Player Player;
/*
 @author
 @date
 @brief crea el jugador a partir de la id
 @param Id, id del jugador
 @param2 nombre de jugador
 @return NULL si algo ha fallado
 @return newplayer
*/
Player * player_create(char *, Id, Id, Id);
/*
 @author
 @date
 @brief destruye el jugador indicado liberando la memoria que lo contiene
 @param Player* es el jugador a eliminar
*/
void player_destroy(Player *);
/*
 @author
 @date
 @brief modifica el nombre de un jugador
 @param Player * jugador al cual establecer el nombre
 @param char * nombre que se desea establecer
 @return ERROR si algo ha fallado
 @return OK
*/
STATUS player_setName(Player *, char *);
/*
@author
@date
@brief cmodifica el id del espacio en el que se encuentra el jugador
@param jugador del cual se desea modifica rla localizacion
@param id del espacio nuevo.
@return OK
@return ERROR si algo ha fallado.
*/
STATUS player_setLocId(Player *, Id);
/*
@authorç
@date
@brief modifica el objeto indicado
@param Player * jugador al que se le desea modificar el objeto
@param Id es el id del objeto
@return ERROR si algo ha fallado
@return OK
*/
STATUS player_setObjId(Player *, Id);
/*
@author
@date
@brief modifica el id de un jugador
@param jugador del cual se desea modificar id
@param el id nuevo
@return OK
@return ERROR si hubo alguno.
*/
STATUS player_setId(Player *, Id);
/*
@author
@date
@brief obtiene el nombre a partir del jugador indicado
@param Player* jugador del que se desea obtener el nombre
@return ERROR si algo ha fallado
@return OK
*/
char * player_getName(Player *);
/*
@author
@date
@brief obtiene el id del espacio donde se encuentra el jugador
@param jugador del cual se desea obtener su localización
@return NULL si algo ha fallado
@return id del espacio
*/
Id player_getLocId(Player *);
/*
@author
@date
@brief obtiene el id de un objeto.
@param el jugador
@param Id
@return NULL si algo ha fallado
@return el id del objeto
*/
Id player_getObjId(Player *, int);
/*
@author
@date
@brief obtiene el id del jugador
@param el jugadr del que se desea obtener el id
@return NULL si algo ha fallado
@return el id 
*/
Id player_getId(Player *);
/*
@author
@date
@brief elimina el id de un objeto que porta un jugador
@param el jugador que porta el objeto
@param el id que se desea eliminar
@return OK
@return ERROR si algo ha fallado
*/

STATUS player_removeObjId(Player *, Id);

#endif
