#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  char gdesc[3][21];
  Set * objects;
};

Space* space_create(Id id)
{

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL)
  {
    return NULL;
  }

  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->objects = set_create(5);

  return newSpace;
}

STATUS space_destroy(Space* space)
{
  if (!space)
  {
    return ERROR;
  }

  set_destroy(space->objects);

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_name(Space* space, char* name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }

  return OK;
}

STATUS space_set_north(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

STATUS space_set_south(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_east(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_west(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->west = id;
  return OK;
}

STATUS space_add_object(Space* space, Id obj_id)
{
  if (!space) return ERROR;

  return set_add(space->objects, obj_id);
}

STATUS space_remove_object(Space* space, Id id)
{
  if (!space) return ERROR;

  return set_del(space->objects, id);
}

const char * space_get_name(Space* space)
{
  if (!space) return NULL;

  return space->name;
}

Id space_get_id(Space* space)
{
  if (!space) return NO_ID;

  return space->id;
}

Id space_get_north(Space* space)
{
  if (!space) return NO_ID;

  return space->north;
}

Id space_get_south(Space* space)
{
  if (!space) return NO_ID;

  return space->south;
}

Id space_get_east(Space* space)
{
  if (!space) return NO_ID;

  return space->east;
}

Id space_get_west(Space* space)
{
  if (!space) return NO_ID;

  return space->west;
}



Set * space_get_objects_id(Space* space)
{
  Set * set;
  int n;

  if (!space) return FALSE;

  set = set_create(5);
  if(!set) return NULL;

  for(n=0; set_get_id(space->objects, n) != NO_ID; n++)
  {
    if(set_add(set, set_get_id(space->objects, n)) == ERROR) return NULL;
  }

  return set;
}

STATUS space_print(Space* space)
{
  Id idaux = NO_ID;

  if (!space) return ERROR;

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No north link.\n");

  idaux = space_get_south(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No south link.\n");

  idaux = space_get_east(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No east link.\n");

  idaux = space_get_west(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No west link.\n");

  if (space_get_objects_id(space))
    set_print_debug(stdout, space->objects);
  else
  {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  return OK;
}

STATUS space_set_gdesc_0(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[0], cadena))return ERROR;
  return OK;
}

STATUS space_set_gdesc_1(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[1], cadena)) return ERROR; 
  return OK;
}

STATUS space_set_gdesc_2(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[2], cadena)) return ERROR;

  return OK;
}

char* space_get_gdesc_0(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[0];
}

char* space_get_gdesc_1(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[1];
}

char* space_get_gdesc_2(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[2];
}
