/**
 * @brief Functions for the creation of objects
 *
 * @file object.c
 * @author Pablo S�nchez y Guillermo R�os
 * @copyright GNU Public License
 */

#include <string.h>

#include "../include/object.h"

struct _Object
{
	char name[STDSIZE];	   /*!< Nombre del objeto*/
	char description[STDSIZE];    /*!< Descripcion del objeto*/
	Id id;			      /*!< Identificador */
	BOOL mobile;		      /*!< indica si es movible o no */
	BOOL moved;		      /*!< indica si se ha movido o no */
	BOOL hidden;		      /*!< indica si el objeto esta oculto */
	Id open;		      /* Indica la id que abre */
	BOOL iluminati;		      /* Indica si ilumina o no */
	BOOL on;		      /* Indica si el objeto esta encendido*/
	char description_al[STDSIZE]; /*!< Descripcion alternativa del objeto*/
};

Object *object_create(char *name, Id id)
{
	Object *obj;

	obj = calloc(1, sizeof(Object));
	if (!obj) return NULL;

	obj->id = id;
	strcpy(obj->name, name);

	obj->mobile = FALSE;
	obj->moved = FALSE;
	obj->hidden = FALSE;
	obj->open = NO_ID;
	obj->iluminati = FALSE;
	obj->on = FALSE;

	return obj;
}

void object_destroy(Object *obj)
{
	if (!obj)
		return;

	free(obj);
}

STATUS object_set_name(Object *obj, char *name)
{
	if (!obj || !name)
		return ERROR;

	if (!strcpy(obj->name, name))
		return ERROR;

	return OK;
}

STATUS object_set_description(Object *obj, char *description)
{
	if (!obj || !description)
		return ERROR;

	if (!strcpy(obj->description, description))
		return ERROR;

	return OK;
}

STATUS object_set_id(Object *obj, Id id)
{
	if (!obj)
		return ERROR;

	obj->id = id;

	return OK;
}

char *object_get_name(Object *obj)
{
	if (!obj)
		return NULL;

	return obj->name;
}

char *object_get_description(Object *obj)
{
	if (!obj)
		return NULL;

	return obj->description;
}
STATUS object_description_print(Object *obj, FILE *f)
{
	if (!obj || !f)
		return ERROR;

	fprintf(f, "%s", obj->description);

	return OK;
}

Id object_get_id(Object *obj)
{
	if (!obj)
		return -1;

	return obj->id;
}
BOOL object_get_mobile(Object *obj)
{
	if (!obj)
		return FALSE;

	return obj->mobile;
}

STATUS object_set_mobile(Object *obj, BOOL mobile)
{
	if (!obj)
		return ERROR;

	obj->mobile = mobile;

	return OK;
}

BOOL object_get_moved(Object *obj)
{
	if (!obj || obj->mobile == FALSE)
		return FALSE;

	return obj->moved;
}

STATUS object_set_moved(Object *obj, BOOL moved)
{
	if (!obj || obj->mobile == FALSE)
		return ERROR;

	obj->moved = moved;

	return OK;
}

BOOL object_get_hidden(Object *obj)
{
	if (!obj)
		return FALSE;

	return obj->hidden;
}

STATUS object_set_hidden(Object *obj, BOOL hidden)
{
	if (!obj)
		return ERROR;

	obj->hidden = hidden;

	return OK;
}

BOOL object_get_iluminati(Object *obj)
{
	if (!obj)
		return FALSE;

	return obj->iluminati;
}

STATUS object_set_ilumnati(Object *obj, BOOL iluminati)
{
	if (!obj)
		return ERROR;

	obj->iluminati = iluminati;

	return OK;
}

Id object_get_open(Object *obj)
{
	if (!obj)
		return -1;

	return obj->open;
}

STATUS object_set_open(Object *obj, Id open)
{
	if (!obj)
		return ERROR;

	obj->open = open;

	return OK;
}

BOOL object_get_on(Object *obj)
{
	if (!obj || obj->iluminati == FALSE)
		return FALSE;

	return obj->on;
}

STATUS object_set_on(Object *obj, BOOL on)
{
	if (!obj || obj->iluminati == FALSE)
		return ERROR;

	obj->on = on;

	return OK;
}

char *object_get_description_alternative(Object *obj)
{
	if (!obj)
		return NULL;

	return obj->description_al;
}

STATUS object_set_description_alternative(Object *obj, char *description_al)
{
	if (!obj || !description_al)
		return ERROR;

	if (!strcpy(obj->description_al, description_al))
		return ERROR;

	return OK;
}

STATUS object_description_al_print(Object *obj, FILE *f)
{
	if (!obj || !f)
		return ERROR;

	fprintf(f, "%s", obj->description_al);

	return OK;
}