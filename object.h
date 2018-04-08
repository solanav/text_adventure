#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"



/*@param un campo de identificacion id
@param nombre del objeto name
*/
typedef struct _Object Object;

/* 

@brief Crea object_create que reserva memoria
@param1 Este inicializa con el puntero id los campos del objeto que devuelve
*/
Object* object_create(char* name, Id id);
/* 
@brief destruye un objeto liberando la memoria que lo contiene
@param puntero object de tipo Object
@return devuelve OK si se ha realizado correctamente o ERROR si no.
*/
void object_destroy(Object* obj);
/* 
@brief modifica el nombre de un objeto
@param puntero object de tipo Object
@param puntero name de tipo char
@return devuelve object->name (el nombre del objeto) o NULL si algo ha fallado 
*/
STATUS object_set_name(Object* obj, char* name);
/*
@brief modifica la id del objeto 
@param puntero object de tipo Object
@param el id del objeto
@return devuelve OK si se ha modificado correctamente o ERROR si no
*/
STATUS object_set_id(Object* obj, Id id);
/* 
@brief Devuelve el nombre de un objeto
@param puntero object de tipo Object
@return devuelve object->name (el nombre del objeto) o NULL si algo ha fallado 
*/
char * object_get_name(Object* obj);
/*
@brief Nos da la id del objecto
@param puntero object de tipo Object
@return nos devuelve NO_ID si el objeto es nulo o el id del objeto
*/
Id object_get_id(Object* obj);

#endif
