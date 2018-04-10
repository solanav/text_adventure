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
	char name [STDSIZE];
	char description[STDSIZE];
	Id id;
};

Object* object_create(char* name, Id id)
{
	Object *obj;

	obj = calloc(1, sizeof(Object));
	if(!obj){return NULL;}

	obj->id = id;
	strcpy(obj->name, name);

	return obj;
}

void object_destroy(Object* obj)
{
	if(!obj) return;

	free(obj);
}

STATUS object_set_name(Object* obj, char* name)
{
	if(!obj||!name) return ERROR;

	if(!strcpy(obj->name, name)) return ERROR;

	return OK;
}

STATUS object_set_description(Object* obj, char* description)
{
	if(!obj||!description) return ERROR;

	if(!strcpy(obj->description, description)) return ERROR;

	return OK;
}

STATUS object_set_id(Object* obj, Id id)
{
	if(!obj) return ERROR;

	obj->id = id;

	return OK;
}

char * object_get_name(Object* obj)
{
	if(!obj) return NULL;

	return obj->name;
}

char * object_get_description(Object* obj)
{
	if(!obj) return NULL;

	return obj->description;
}

Id object_get_id(Object* obj)
{
	if(!obj) return -1;

	return obj->id;
}
