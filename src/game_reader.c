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


STATUS game_save(Game * game, char * filename)
{
	FILE * f;
	int i, j;

	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};
	char  aux[WORD_SIZE];

	Id id = NO_ID, place = NO_ID, sprite_id = NO_ID, opens = NO_ID, link0 = NO_ID, link1 = NO_ID;
	BOOL light, mobile, hidden, on, lights;

	int direction;

	Space * space = NULL;
	Object * object = NULL;
	Link * link = NULL;
	Player * player = NULL;

	LinkStatus door;

	sprintf(aux, "saves/%s.sv", filename);

	f = fopen(aux, "w");
	if(!f) return ERROR;

	/*SPACES*/
	for(i = 0; (id = game_get_space_id_at(game, i)) != NO_ID && i<MAX_SPACES; i++)
	{
		space = game_get_space(game, id);
		fprintf(f, "#s:");
		fprintf(f, "%ld|", id);
		strcpy(name, space_get_name(space));
		fprintf(f, "%s|", name);
		strcpy(description, space_get_description(space));
		fprintf(f, "%s|", description);
		light = space_get_light(space);
		fprintf(f, "%d|", light);
		for(j = 0; j <= 16; j++)
		{
			sprite_id = space_getSprite(space, i);
			fprintf(f, "%ld|", sprite_id);
		}
		fprintf(f, "\n");
	}
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

	/*PLAYER LOCATION*/
	id = game_get_player_location(game);
	fprintf(f, "#c:%ld|\n", id);

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

STATUS game_load_spaces(Game *, FILE *);
STATUS game_load_objects(Game *, FILE *);
STATUS game_load_player_objects(Game *, FILE *);
STATUS game_load_player_location(Game *, FILE *);
STATUS game_load_links(Game *, FILE *);

STATUS game_load(Game * game, char * filename)
{
	FILE * f;
	STATUS flag = OK;
	char aux[WORD_SIZE];

	if(strcmp(filename, "data/data.dat") != 0)
	{
		sprintf(aux, "saves/%s.sv", filename);
		game_destroy(game);
		game = game_create();
	}
	else
		strcpy(aux, filename);

	f = fopen(aux, "r");
	if(!f) return ERROR;


	flag = game_load_spaces(game, f);
	rewind(f);
	flag = game_load_objects(game, f);
	rewind(f);
	flag = game_load_player_objects(game, f);
	rewind(f);
	flag = game_load_player_location(game, f);
	rewind(f);
	flag = game_load_links(game, f);

	return flag;
}

STATUS game_load_spaces(Game *game, FILE * f)
{
	/*
	* Loads game spaces from specified file.
	*
	* game: the main game structure
	* filename: .dat file you want to use
	*
	* returns: ERROR or OK
	*/

	char *toks = NULL;
	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};

	Id id = NO_ID, sprite_id[16];

	int i;
	BOOL light;

	Space *space = NULL;


	if (!f || !game)
	return ERROR;

	while (fgets(line, WORD_SIZE, f))
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
	}

	return OK;
}

STATUS game_load_objects(Game * game, FILE * f)
{
	char *toks = NULL;
	char line[WORD_SIZE] = {0};
	char name[WORD_SIZE] = {0};
	char description[WORD_SIZE] = {0};

	Id id = NO_ID, place = NO_ID, opens = NO_ID;
	BOOL mobile, hidden, on, lights;

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

			game_add_object(game, object_create(name, id, mobile, hidden, opens, lights, on));
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

STATUS game_load_player_location(Game * game, FILE * f)
{
	char * toks = NULL;
	char line[WORD_SIZE] = {0};

	Id loc_id;

	while(fgets(line, WORD_SIZE, f))
	{
		if(strncmp("#c:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			loc_id = atol(toks);
			game_set_player_location(game, loc_id);
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
			direction = atoi(toks);

			toks = strtok(NULL, "|");
			door = atoi(toks);

			game_set_link(game, id, link0, link1, direction, door);
		}
	}
	return OK;
}
