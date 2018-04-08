#include <string.h>

#include "object.h"


struct _Object{
  char name [STDSIZE];
  Id id;
  char descripton[STDLONGSIZE];
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

STATUS object_set_id(Object* obj, Id id)
{
	if(!obj) return ERROR;

	obj->id = id;

	return OK;
}

STATUS object_set_description(Object * obj, char * descript)
{
	if(!obj || !descript) return ERROR;

	if (!strcpy(obj->descripton, descript)) return ERROR;

	return OK;
}

char* object_get_name(Object* obj)
{
	if(!obj) return NULL;

	return obj->name;
}

Id object_get_id(Object* obj)
{
	if(!obj) return -1;

	return obj->id;
}

char * object_get_description(Object * obj)
{
	if(!obj) return "\0";

	return obj->descripton;
}
