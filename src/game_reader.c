/**
 * @brief Reads data for the game from files
 *
 * @file game_reader.c
 * @author Catalín Rotaru
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game_reader.h"

STATUS game_loadSpaces(Game* game, char* filename)
{
	/*
	* Loads game spaces from specified file.
	*
	* game: the main game structure
	* filename: .dat file you want to use
	*
	* returns: ERROR or OK
	*/

	FILE* file = NULL;

	char * gdesc0=NULL, * gdesc1=NULL, * gdesc2=NULL,* toks = NULL;

	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};
	char no_string[20] = "                 ";

	Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID ;

	Space* space = NULL;
	Object* object = NULL;
	STATUS status = OK;

	if (!filename || !game) return ERROR;

	file = fopen(filename, "r");
	if (file == NULL) return ERROR;

	while (fgets(line, WORD_SIZE, file))
	{
		if (strncmp("#s:", line, 3) == 0)
		{
			/* Read Id */
			toks = strtok(line + 3, "|");
			id = atol(toks);

			/* Read Name */
			toks = strtok(NULL, "|");
			strcpy(name, toks);

			/* Read Description */
			toks = strtok(NULL, "|");
			strcpy(description, toks);

			/* Read North/East/South/West */
			toks = strtok(NULL, "|");
			north = atol(toks);

			toks = strtok(NULL, "|");
			east = atol(toks);

			toks = strtok(NULL, "|");
			south = atol(toks);

			toks = strtok(NULL, "|");
			west = atol(toks);

			gdesc0 = strtok(NULL, "|");
			gdesc1 = strtok(NULL, "|");
			gdesc2 = strtok(NULL, "|");

			/* Create space (only assigns id for now) */
			space = space_create(id);

			/* Save what we just read */
			if (space != NULL)
			{
				space_setName(space, name);
				space_setNorth(space, north);
				space_setEast(space, east);
				space_setSouth(space, south);
				space_setWest(space, west);

				if (gdesc0 == NULL)
					space_setGdesc0(space, no_string);
				else
					space_setGdesc0(space, gdesc0);

				if (gdesc1 == NULL)
					space_setGdesc1(space, no_string);
				else
					space_setGdesc1(space, gdesc1);

				if (gdesc2 == NULL)
					space_setGdesc2(space, no_string);
				else
					space_setGdesc2(space, gdesc2);

				space_setDescription(space, description);

				game_addSpace(game, space);
			}
		}
	}

	if (ferror(file)) {
	status = ERROR;
	}

	fclose(file);

	return status;
}

STATUS game_loadObjects(Game* game, char* filename)
{
	/*
	* Loads game objects from specified file.
	*
	* game: the main game structure
	* filename: .dat file you want to use
	*
	* returns: ERROR or OK
	*/

	FILE* file = NULL;

	char * toks = NULL;

	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};
	/*char no_string[20] = "                 ";*/

	Id id = NO_ID, place = NO_ID;

	STATUS status = OK;

	if (!filename || !game) return ERROR;

	file = fopen(filename, "r");
	if (file == NULL) return ERROR;

	while (fgets(line, WORD_SIZE, file))
	{
		if (strncmp("#s:", line, 3) == 0)
		{
			/* Read Id */
			toks = strtok(line + 3, "|");
			id = atol(toks);

			/* Read Name */
			toks = strtok(NULL, "|");
			strcpy(name, toks);

			/* Read Description */
			toks = strtok(NULL, "|");
			strcpy(description, toks);

			/* Read North/East/South/West */
			toks = strtok(NULL, "|");

			toks = strtok(NULL, "|");

			toks = strtok(NULL, "|");

			toks = strtok(NULL, "|");

		}

		if (strncmp("#o:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);

			toks = strtok(NULL, "|");
			strcpy(name, toks);

			toks = strtok(NULL, "|");
			place = atol(toks);

			toks = strtok(NULL, "|");
			strcpy(description, toks);

			object = object_create(name, id);
			object_set_description(object, description);
			game_set_object(game, object);
			printf("Set location %ld for %s\n", place, name);
			game_set_object_location(game, place, id);
			printf("%ld is in space %ld", id, game_get_object_location(game, id));
		}

		if (strncmp("#l:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);

			toks = strtok(NULL, "|");
			strcpy(name, toks);

			toks = strtok(NULL, "|");
			link0 = atol(toks);

			toks = strtok(NULL, "|");
			link1 = atol(toks);

			printf("LinkId -> %ld, Link0 -> %ld Link1 -> %ld\n", id, link0, link1);

			game_setLink(game, id, link0, link1);
		}
	}

	if (ferror(file)) {
	status = ERROR;
	}

	fclose(file);

	return status;
}


STATUS game_loadAll(Game* game, char* filename)
{
	STATUS a=OK,b=OK,c=OK;
	if (!filename || !game) return ERROR;

	a = game_loadLinks( game, filename);
	b = game_loadSpaces( game,  filename);
	c = game_loadObjects( game,  filename);

	if(a == ERROR || b == ERROR || c == ERROR)
		return ERROR;
	else
		return OK;

}
