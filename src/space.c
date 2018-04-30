/**
 * @brief Defines functions for space manipulation
 *
 * @file command.c
 * @author Catal�n Rotaru
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/space.h"
#include "../include/set.h"

struct _Space
{
	Id id;			     /*!< id del espacio*/
	char name[WORD_SIZE];	     /*!< nombre del espacio*/
	char description[WORD_SIZE]; /*!< descripcion*/
	Id linkNorth;		     /*!< id del link al norte*/
	Id linkSouth;		     /*!< id del link al sur*/
	Id linkEast;		     /*!< id del link al este*/
	Id linkWest;		     /*!< id del link al oeste*/
	Id linkUp;		     /*!< id del link hacia arriba*/
	Id linkDown;		     /*!< id del link hacia abajo*/
	Id spriteId[17];	     /*!< id del sprite*/
	int curentSprite;	     /*!< sprite que actual*/
	char gdesc[3][21];	     /*!< strings para objetos ASCII*/
	Set *objects;		     /*!< Set de objetos*/
	BOOL light;		     /*!< Bool que indica si la casilla esta iluminada*/
};

Space *space_create(Id id)
{
	int i;

	Space *newSpace = NULL;

	if (id == NO_ID)
		return NULL;

	newSpace = (Space *)malloc(sizeof(Space));

	if (newSpace == NULL)
		return NULL;

	newSpace->id = id;

	newSpace->name[0] = '\0';
	newSpace->description[0] = '\0';

	newSpace->linkNorth = NO_ID;
	newSpace->linkSouth = NO_ID;
	newSpace->linkEast = NO_ID;
	newSpace->linkWest = NO_ID;
	newSpace->linkUp = NO_ID;
	newSpace->linkDown = NO_ID;

	for (i = 0; i<=16; i++)
	{
		newSpace->spriteId[i] = NO_ID;
	}

	newSpace->objects = set_create(5);

	return newSpace;
}

STATUS space_destroy(Space *space)
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

STATUS space_set_name(Space *space, char *name)
{
	if (!space || !name)
		return ERROR;

	if (!strcpy(space->name, name))
		return ERROR;

	return OK;
}

STATUS space_setSprite(Space *space, Id spriteId, int i)
{
	if (!space)
		return ERROR;

	space->spriteId[i] = spriteId;

	return OK;
}

STATUS space_setCurrentSprite(Space *space, int i)
{
	if (!space)
		return ERROR;

	space->curentSprite = i;

	return OK;
}

STATUS space_set_description(Space *space, char *description)
{
	if (!space || !description)
		return ERROR;

	if (!strcpy(space->description, description))
		return ERROR;

	return OK;
}

STATUS space_set_north(Space *space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->linkNorth = id;
	return OK;
}

STATUS space_set_south(Space *space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->linkSouth = id;
	return OK;
}

STATUS space_set_east(Space *space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->linkEast = id;
	return OK;
}

STATUS space_set_west(Space *space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->linkWest = id;
	return OK;
}

STATUS space_set_up(Space *space, Id id)
{
	if (!space || id == NO_ID)
		return ERROR;

	space->linkUp = id;

	return OK;
}

STATUS space_set_down(Space *space, Id id)
{
	if (!space || id == NO_ID)
		return ERROR;

	space->linkDown = id;

	return OK;
}

STATUS space_set_light(Space *space, BOOL light)
{
	if (!space)
		return ERROR;
	else if (light != TRUE && light != FALSE)
		return ERROR;

	space->light = light;

	return OK;
}

BOOL space_get_light(Space *space)
{
	if (!space)
		return FALSE;

	return space->light;
}


STATUS space_add_object(Space *space, Id obj_id)
{
	if (!space)
		return ERROR;

	return set_add(space->objects, obj_id);
}

STATUS space_remove_object(Space *space, Id id)
{
	if (!space)
		return ERROR;

	return set_del(space->objects, id);
}

Id space_getSprite(Space *space, int i)
{
	if (!space)
		return ERROR;

	return space->spriteId[i];
}

int space_getCurentSprite(Space *space)
{
	if (!space)
		return ERROR;

	return space->curentSprite;
}

const char *space_get_name(Space *space)
{
	if (!space)
		return NULL;

	return space->name;
}

const char *space_get_description(Space *space)
{
	if (!space)
		return NULL;

	return space->description;
}

Id space_get_id(Space *space)
{
	if (!space)
		return NO_ID;

	return space->id;
}

Id space_get_north(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkNorth;
}

Id space_get_south(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkSouth;
}

Id space_get_east(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkEast;
}

Id space_get_west(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkWest;
}

Id space_get_up(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkUp;
}

Id space_get_down(Space *space)
{
	if (!space)
		return NO_ID;

	return space->linkDown;
}

Set *space_get_objects_id(Space *space)
{
	Set *set;
	int n;

	if (!space)
		return NULL;

	set = set_create(5);
	if (!set)
		return NULL;

	for (n = 0; set_get_id(space->objects, n) != NO_ID; n++)
	{
		if (set_add(set, set_get_id(space->objects, n)) == ERROR)
			return NULL;
	}

	return set;
}
STATUS space_light_print(Space *space)
{

	Id idaux = NO_ID;
	STATUS status;
	if (!space)
		return ERROR;

	if (space->light == TRUE)
	{
		status = space_print(space);
		return status;
	}
	else
	{
		fprintf(stdout, "\n\n--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

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

		idaux = space_get_up(space);
		if (NO_ID != idaux)
			fprintf(stdout, "---> Up link: %ld.\n", idaux);
		else
			fprintf(stdout, "---> No up link.\n");

		idaux = space_get_down(space);
		if (NO_ID != idaux)
			fprintf(stdout, "---> Down link: %ld.\n", idaux);
		else
			fprintf(stdout, "---> No down link.\n");
	}

	return OK;
}

STATUS space_print(Space *space)
{
	Id idaux = NO_ID;
	Set *aux;

	if (!space)
		return ERROR;

	fprintf(stdout, "\n\n--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

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

	idaux = space_get_up(space);
	if (NO_ID != idaux)
		fprintf(stdout, "---> Up link: %ld.\n", idaux);
	else
		fprintf(stdout, "---> No up link.\n");

	idaux = space_get_down(space);
	if (NO_ID != idaux)
		fprintf(stdout, "---> Down link: %ld.\n", idaux);
	else
		fprintf(stdout, "---> No down link.\n");

	if ((aux = space_get_objects_id(space)))
	{
		set_print_debug(stdout, space->objects);
		set_destroy(aux);
	}
	else
	{
		fprintf(stdout, "---> No objects in the space.\n");
	}

	return OK;
}

STATUS space_set_gdesc_0(Space *space, char *cadena)
{
	if (!space || !cadena)
		return ERROR;

	if (!strcpy(space->gdesc[0], cadena))
		return ERROR;
	return OK;
}

STATUS space_set_gdesc_1(Space *space, char *cadena)
{
	if (!space || !cadena)
		return ERROR;

	if (!strcpy(space->gdesc[1], cadena))
		return ERROR;
	return OK;
}

STATUS space_set_gdesc_2(Space *space, char *cadena)
{
	if (!space || !cadena)
		return ERROR;

	if (!strcpy(space->gdesc[2], cadena))
		return ERROR;

	return OK;
}

char *space_get_gdesc_0(Space *space)
{
	if (space == NULL)
		return NULL;

	return space->gdesc[0];
}

char *space_get_gdesc_1(Space *space)
{
	if (space == NULL)
		return NULL;

	return space->gdesc[1];
}

char *space_get_gdesc_2(Space *space)
{
	if (space == NULL)
		return NULL;

	return space->gdesc[2];
}
/*
char *space_getSprite(Space *space, int line)
{
	if (space == NULL)
		return NULL;

	return space->sprite[line];
}

STATUS space_setSprite(Space *space, char *sprite_line, int line)
{
	if (space == NULL || sprite_line == NULL)
		return ERROR;

	strcpy(space->sprite[line], sprite_line);

	return OK;
}

BOOL space_isLinked(Space*)*/
