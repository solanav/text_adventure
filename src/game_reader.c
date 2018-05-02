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

STATUS game_load_spaces(Game *game, char *filename)
{
	/*
	* Loads game spaces from specified file.
	*
	* game: the main game structure
	* filename: .dat file you want to use
	*
	* returns: ERROR or OK
	*/

	FILE *file = NULL;

	char *toks = NULL;
	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};

	Id id = NO_ID, place = NO_ID, sprite_id[16], link0 = NO_ID, link1 = NO_ID, opens = NO_ID;

	int direction, i, j = 0;
	BOOL light, mobile, hidden, on, lights;

	Space *space = NULL;
	STATUS status = OK;
	LinkStatus door;

	if (!filename || !game)
		return ERROR;

	file = fopen(filename, "r");
	if (file == NULL)
		return ERROR;

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

			/* Read Light */
			toks = strtok(NULL, "|");
			light = atoi(toks);

			/* Read Sprites */
			for (i = 0; i <= 16; i++)
			{
				toks = strtok(NULL, "|");
				sprite_id[i] = atol(toks);
			}

			/* Create space (only assigns id for now) */
			space = space_create(id);

			printf("Created space [%d]\n", j);
			j++;

			/* Save what we just read */
			if (space != NULL)
			{
				space_set_name(space, name);
				space_set_description(space, description);
				space_set_light(space, light);

				printf("%s => lights %d\n", space_get_name(space), space_get_light(space));

				for (i = 0; i <= 16; i++)
				{
					printf("- Saving %ld in %d\n", sprite_id[i], i);
					space_setSprite(space, sprite_id[i], i);
				}

				game_add_space(game, space);
			}

			printf("|");
			for (i = 0; i <= 16; i++)
				printf("%ld|", space_getSprite(space, i));
			printf("\n\n");
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

			toks = strtok(NULL, "|");
			mobile = atoi(toks);

			toks = strtok(NULL, "|");
			hidden = atoi(toks);

			toks = strtok(NULL, "|");
			opens = atol(toks);

			toks = strtok(NULL, "|");
			lights = atoi(toks);

			toks = strtok(NULL, "|");
			on = atoi(toks);

			printf("DATA\n");
			printf("\tname %s\n", name);
			printf("\tid   %ld\n", id);
			printf("\tspce %ld\n", place);
			printf("\tdesc %s\n", description);
			printf("\tmob  %d\n", mobile);
			printf("\thid  %d\n", hidden);
			printf("\topns %ld\n", opens);
			printf("\tlit? %d\n", lights);
			printf("\ton   %d\n\n", on);

			game_add_object(game, object_create(name, id, mobile, hidden, opens, lights, on));
			game_set_object_location(game, place, id, name, description);
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

			toks = strtok(NULL, "|");
			direction = atol(toks);

			toks = strtok(NULL, "|");
			door = atoi(toks);

			printf("Door %d\n", door);

			game_set_link(game, id, link0, link1, direction, door);
		}
	}

	if (ferror(file))
	{
		status = ERROR;
	}

	fclose(file);

	printf("Reading of game complete...\n");

	return status;
}
