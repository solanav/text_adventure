/**
 * @brief Functions for the creation of objects
 *
 * @file object.c
 * @author Pablo Sánchez y Guillermo Ríos
 * @copyright GNU Public License
 */

#include <string.h>

#include "../include/object.h"

struct _Object{
	char name [STDSIZE]; /*!< Nombre del objeto*/
	char description[STDSIZE]; /*!< Descripcion del objeto*/
	Id id; /*!< Identificador */
	BOOL moved;/*!< */
};

Object * object_create(char * name, Id id)
{
	Object * obj;

	obj = calloc(1, sizeof(Object));
	if(!obj){return NULL;}

	obj->id = id;
	strcpy(obj->name, name);

	return obj;
}

void object_destroy(Object * obj)
{
	if(!obj) return;

	free(obj);
}

STATUS object_setName(Object * obj, char * name)
{
	if(!obj||!name) return ERROR;

	if(!strcpy(obj->name, name)) return ERROR;

	return OK;
}

STATUS object_setDescription(Object * obj, char * description)
{
	if(!obj||!description) return ERROR;

	if(!strcpy(obj->description, description)) return ERROR;

	return OK;
}

STATUS object_setId(Object * obj, Id id)
{
	if(!obj) return ERROR;

	obj->id = id;

	return OK;
}

char * object_getName(Object * obj)
{
	if(!obj) return NULL;

	return obj->name;
}

char * object_getDescription(Object * obj)
{
	if(!obj) return NULL;

	return obj->description;
}

Id object_getId(Object* obj)
{
	if(!obj) return -1;

	return obj->id;
}
/*nuevas funcines */
/*BOOL * objetc_setMoved (Object * obj, Id id )
{
	if (!obj || id == NO_ID) return FALSE;

	obj->moved = id;

	return TRUE;
}no se cual de las dos esta mejor*/

BOOL object_getMoved(Object * obj)
{
	if(!obj)
		return FALSE;

	return obj->moved;
}

STATUS object_setMoved(Object * obj, BOOL moved)
{
	if(!obj)
		return ERROR;
	else if(moved!=TRUE && moved!=FALSE)
		return ERROR;
	obj->moved=moved;

	return OK;
}
