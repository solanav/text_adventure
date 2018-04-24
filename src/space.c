/**
 * @brief Defines functions for space manipulation
 *
 * @file command.c
 * @author Catalín Rotaru
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/space.h"
#include "../include/set.h"

struct _Space {
	Id id; /*!< id del espacio*/
	char name[WORD_SIZE]; /*!< nombre del espacio*/
	char description[WORD_SIZE]; /*!<  descripcion*/
	Id linkNorth; /*!< id del link al norte*/
	Id linkSouth; /*!< id del link al sur*/
	Id linkEast; /*!< id del link al este*/
	Id linkWest; /*!< id del link al oeste*/
	char gdesc[3][21]; /*!< strings para objetos ASCII*/
	Set * objects; /*!< Set de objetos*/
};

Space * space_create(Id id)
{
	Space * newSpace = NULL;

	if (id == NO_ID) return NULL;

	newSpace = (Space *) malloc(sizeof (Space));

	if (newSpace == NULL) return NULL;

	newSpace->id = id;

	newSpace->name[0] = '\0';
	newSpace->description[0] = '\0';

	newSpace->linkNorth = NO_ID;
	newSpace->linkSouth = NO_ID;
	newSpace->linkEast = NO_ID;
	newSpace->linkWest = NO_ID;

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

STATUS space_setName(Space* space, char* name)
{
	if (!space || !name) return ERROR;

	if (!strcpy(space->name, name)) return ERROR;

	return OK;
}

STATUS space_setDescription(Space* space, char* description)
{
	if (!space || !description) return ERROR;

	if (!strcpy(space->description, description)) return ERROR;

	return OK;
}

STATUS space_setNorth(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->linkNorth = id;
  return OK;
}

STATUS space_setSouth(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->linkSouth = id;
  return OK;
}

STATUS space_setEast(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->linkEast = id;
  return OK;
}

STATUS space_setWest(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->linkWest = id;
  return OK;
}

STATUS space_addObject(Space* space, Id obj_id)
{
  if (!space) return ERROR;

  return set_add(space->objects, obj_id);
}

STATUS space_removeObject(Space* space, Id id)
{
  if (!space) return ERROR;

  return set_del(space->objects, id);
}

const char * space_getName(Space* space)
{
  if (!space) return NULL;

  return space->name;
}

const char * space_getDescription(Space* space)
{
  if (!space) return NULL;

  return space->description;
}

Id space_getId(Space* space)
{
  if (!space) return NO_ID;

  return space->id;
}

Id space_getNorth(Space* space)
{
  if (!space) return NO_ID;

  return space->linkNorth;
}

Id space_getSouth(Space* space)
{
  if (!space) return NO_ID;

  return space->linkSouth;
}

Id space_getEast(Space* space)
{
  if (!space) return NO_ID;

  return space->linkEast;
}

Id space_getWest(Space* space)
{
  if (!space) return NO_ID;

  return space->linkWest;
}

Set * space_getObjectsId(Space* space)
{
  Set * set;
  int n;

  if (!space) return NULL;

  set = set_create(5);
  if(!set) return NULL;

  for(n=0; set_getId(space->objects, n) != NO_ID; n++)
  {
    if(set_add(set, set_getId(space->objects, n)) == ERROR) return NULL;
  }

  return set;
}

STATUS space_print(Space* space)
{
  Id idaux = NO_ID;
  Set * aux;

  if (!space) return ERROR;

  fprintf(stdout, "\n\n--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_getNorth(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No north link.\n");

  idaux = space_getSouth(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No south link.\n");

  idaux = space_getEast(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No east link.\n");

  idaux = space_getWest(space);
  if (NO_ID != idaux)
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  else
    fprintf(stdout, "---> No west link.\n");

  if ((aux = space_getObjectsId(space)))
  {
    set_printDebug(stdout, space->objects);
		set_destroy(aux);
  }
  else
  {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  return OK;
}

STATUS space_setGdesc0(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[0], cadena))return ERROR;
  return OK;
}

STATUS space_setGdesc1(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[1], cadena)) return ERROR;
  return OK;
}

STATUS space_setGdesc2(Space* space, char* cadena)
{
  if (!space || !cadena) return ERROR;

  if (!strcpy(space->gdesc[2], cadena)) return ERROR;

  return OK;
}

char* space_getGdesc0(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[0];
}

char* space_getGdesc1(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[1];
}

char* space_getGdesc2(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[2];
}

/*BOOL space_isLinked(Space*)*/
