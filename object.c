#include "object.h"
#include <string.h>

struct _Object{
  char name [STDSIZE];
  Id id;
};

Object* obj_create(char* name, Id id)
{
  Object *obj;

  obj = calloc(1, sizeof(Object));
  if(!obj){return NULL;}

  obj->id = id;
  strcpy(obj->name, name);

  return obj;
}

void obj_destroy(Object* obj)
{
  if(!obj){return;}

  free(obj);
}

STATUS obj_setName(Object* obj, char* name)
{
  if(!obj||!name) return ERROR;

  if(!strcpy(obj->name, name)) return ERROR;

  return OK;
}

STATUS obj_setId(Object* obj, Id id)
{
  if(!obj){return ERROR;}

  obj->id = id;

  return OK;
}

char* obj_getName(Object* obj)
{
  if(!obj){return NULL;}

  return obj->name;
}

Id obj_getId(Object* obj)
{
  if(!obj){return -1;}

  return obj->id;
}
