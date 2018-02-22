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
  return;
}

Object* obj_setName(Object* obj, char* name)
{
  if(!obj||!name){return NULL;}

  strcpy(obj->name, name);

  return obj;
}

Object* obj_setId(Object* obj, Id id)
{
  if(!obj){return NULL;}

  obj->id = id;

  return obj;
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
