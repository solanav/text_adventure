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

	Id id = NO_ID, place = NO_ID, sprite_id[16];
	Id link0 = NO_ID, link1 = NO_ID;

	int direction, i, j = 0;

	Space *space = NULL;
	STATUS status = OK;

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

			/* Read Sprites */
			for (i=0; i<=16; i++)
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
				space_setSprite(space, sprite_id[0], 0);

				game_add_space(game, space);
			}
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

			game_set_link(game, id, link0, link1, direction);
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
