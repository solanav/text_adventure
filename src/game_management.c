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

STATUS game_load_spaces(Game* game, char* filename)
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

	Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, place = NO_ID;
	Id link0 = NO_ID, link1 = NO_ID;

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
				space_set_name(space, name);
				space_set_north(space, north);
				space_set_east(space, east);
				space_set_south(space, south);
				space_set_west(space, west);

				if (gdesc0 == NULL)
					space_set_gdesc_0(space, no_string);
				else
					space_set_gdesc_0(space, gdesc0);

				if (gdesc1 == NULL)
					space_set_gdesc_1(space, no_string);
				else
					space_set_gdesc_1(space, gdesc1);

				if (gdesc2 == NULL)
					space_set_gdesc_2(space, no_string);
				else
					space_set_gdesc_2(space, gdesc2);

				space_set_description(space, description);

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

			game_set_link(game, id, link0, link1);
		}
	}

	if (ferror(file)) {
	status = ERROR;
	}

	fclose(file);

	return status;
}

STATUS game_save_on_file(Game * game, char* savefile)
{
	int i, j[2]={2, 3};
	char * string;
	FILE * save;
	Player * ply;
	Object * obj;
	Space * spc;
	Link * lnk;
	Die * die;
	Id location;

	if(!game || !savefile) return ERROR;

	sprintf(string, "../saves/%s.sv", savefile);

	save = fopen(string, w);
	if(!save) return ERROR;

	/*OBJECTS*/
	obj = game_get_object_from_id(game_get_object_id_at(game, 0));
	location = game_get_object_location(game_get_object_id_at(game, 0));

	for (i = 1; i<MAX_OBJECTS || obj != NULL;  i++);
	{
		fwrite(&obj, sizeof(struct Object), 1, save);
		fwrite(&location, sizeof(long int), 1, save);
		obj = game_get_object_from_id(game_get_object_id_at(game, i));
		location = game_get_object_location(game_get_object_id_at(game, i));
	}

	fwrite(j, sizeof(j), 2, save);

	/*PLAYER*/

	ply = game_get_player(game);
	location = game_get_player_location(game);

	fwrite(&ply, sizeof(struct Player), 1, save);
	fwrite(location, sizeof(long int), 1, save);

	fwrite(j, sizeof(j), 2, save);

	/*SPACES*/

	spc = game_get_space(game_get_space_id_at(game, 0));

	for (i = 1; i<MAX_SPACES || spc != NULL;  i++)
	{
		fwrite(&spc, sizeof(struct Space), 1, save);
		spc = game_get_space(game_get_space_id_at(game, 1));
	}

	fwrite(j, sizeof(j), 2, save);

	/*LINKS*/

	lnk = game_get_link(game_get_link_id_at(game, 0));

	for (i = 1; i<MAX_LINK || lnk != NULL;  i++)
	{
		fwrite(&lnk, sizeof(struct Link), 1, save);
		lnk = game_get_link(game_get_link_id_at(game, 0));
	}

	fwrite(j, sizeof(j), 2, save);

	/*DIE*/

	die = game_get_die();

	fwrite(&die, sizeof(struct Die), 1, save);

	fwrite(j, sizeof(j), 2, save);

	fclose(save);
}

STATUS game_load_from_file(Game * game, char * savefile)
{
	int r=0;
	char * string;
	FILE * save;
	Player * ply;
	Object * obj;
	Space * spc;
	Link * lnk;
	Die * die;
	Id location;
	Game * new;

	if(!game || !savefile) return ERROR;

	sprintf(string, "../saves/%s.sv", savefile);

	game_destroy(game);
	game = game_create();

	save = fopen(string, r);
	if(!save) return ERROR;

	r = fread(&obj, sizeof(struct obj), 1, save);
	while(r != 2){
		game_set_object(game, obj);
		r = fread(&obj, sizeof(struct obj), 1, save);
	}

	r = fread(&ply, sizeof(struct Player), 1, save);
	


}
