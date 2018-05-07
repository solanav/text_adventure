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

			j++;

			/* Save what we just read */
			if (space != NULL)
			{
				space_set_name(space, name);
				space_set_description(space, description);
				space_set_light(space, light);

				for (i = 0; i <= 16; i++)
				{
					space_setSprite(space, sprite_id[i], i);
				}

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

			game_set_link(game, id, link0, link1, direction, door);
		}
	}

	if (ferror(file))
	{
		status = ERROR;
	}

	fclose(file);

	return status;
}

STATUS game_save(Game * game, char * filename)
{
	FILE * f;
	int i;

	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};
	char  aux[WORD_SIZE];

	Id id = NO_ID, place = NO_ID, opens = NO_ID, link0 = NO_ID, link1 = NO_ID;
	BOOL mobile, hidden, on, lights;

	int direction;

	Object * object = NULL;
	Link * link = NULL;
	Player * player;

	LinkStatus door;

	sprintf(aux, "saves/%s.sv", filename);

	f = fopen(aux, "w");
	if(!f) return ERROR;

	/*OBJECTS*/
	for(i = 0; (id = game_get_object_id_at(game, i)) != NO_ID && i < MAX_OBJECTS; i++)
	{
		object = game_get_object_from_id(game, id);
		fprintf(f, "#o:");
		fprintf(f, "%ld|", id);
		strcpy(name, object_get_name(object));
		fprintf(f, "%s|", name);
		place = game_get_object_location(game, id);
		fprintf(f, "%ld|", place);
		strcpy(description, object_get_description(object));
		fprintf(f, "%s|", description);
		mobile = object_get_mobile(object);
		fprintf(f, "%d|", mobile);
		hidden = object_get_hidden(object);
		fprintf(f, "%d|", hidden);
		opens = object_get_open(object);
		fprintf(f, "%ld|", opens);
		lights = object_get_iluminati(object);
		fprintf(f, "%d|", lights);
		on = object_get_on(object);
		fprintf(f, "%d|\n", on);
	}

	/*PLAYER OBJECTS*/
	player = game_get_player(game);
	for(i = 0; (id = player_getObjId(player, i)) != NO_ID && i < MAX_INV_SIZE; i++)
	{
		fprintf(f, "#p:%ld|\n", id);
	}

	/*LINKS*/
	for(i = 0; (id = game_get_link_id_at(game, i)) != NO_ID && i < MAX_LINK; i++)
	{
		link = game_get_link(game, id);
		fprintf(f, "#l:");
		fprintf(f, "%ld|", id);
		sprintf(name, "Link %d", i+1);
		fprintf(f, "%s|", name);
		link0 = link_getSpace1(link);
		fprintf(f, "%ld|", link0);
		link1 = link_getSpace2(link);
		fprintf(f, "%ld|", link1);
		direction = link_getDirection(link);
		fprintf(f, "%d|", direction);
		door = link_getStatus(link);
		fprintf(f, "%d|\n", door);
	}

	return OK;
}

STATUS game_load_objects(Game *, FILE *);
STATUS game_load_player_objects(Game *, FILE *);
STATUS game_load_links(Game *, FILE *);

STATUS game_load(Game * game, char * filename)
{
	FILE * f;
	STATUS flag = OK;
	char aux[WORD_SIZE];

	sprintf(aux, "saves/%s.sv", filename);

	f = fopen(aux, "r");
	if(!f) return ERROR;

	flag = game_load_objects(game, f);
	rewind(f);
	flag = game_load_player_objects(game, f);
	rewind(f);
	flag = game_load_links(game, f);

	return flag;
}

STATUS game_load_objects(Game * game, FILE * f)
{
	char *toks = NULL;
	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};

	Id id = NO_ID, place = NO_ID, opens = NO_ID;
	BOOL mobile, hidden, on, lights;

	Object * obj = NULL;

	while(fgets(line, WORD_SIZE, f)){
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

			obj = game_get_object_from_id(game, id);
			if(obj == NULL)
			{
				obj = object_create(name, id, mobile, hidden, opens, lights, on);
			}
			else
			{
				object_set_mobile(obj, mobile);
				object_set_hidden(obj, hidden);
				object_set_open(obj, opens);
				object_set_ilumnati(obj, lights);
				object_set_on(obj, on);
			}
			game_set_object_location(game, place, id, name, description);
		}

	}
	return OK;
}

STATUS game_load_player_objects(Game * game, FILE * f)
{
	char *toks = NULL;
	char line[WORD_SIZE] = {0};

	Id id = NO_ID;

	Player * player = NULL;

	while(fgets(line, WORD_SIZE, f))
	{
		if(strncmp("#p:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);

			player = game_get_player(game);
			player_setObjId(player, id);
		}
	}
	return OK;
}

STATUS game_load_links(Game * game, FILE * f)
{
	char *toks = NULL;
	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};

	Id id = NO_ID, link0 = NO_ID, link1 = NO_ID;

	int direction;

	Link * link = NULL;
	LinkStatus door;

	while(fgets(line, WORD_SIZE, f))
	{
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

			link = game_get_link(game, id);
			if(link == NULL)
			{
				link = link_create(id);
			}
			link_setDirection(link, direction);
			link_setStatus(link, door);
			link_setSpaces(link, link0, link1);
		}
	}
	return OK;
}
