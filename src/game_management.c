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

#include "../include/game_management.h"

STATUS game_load(Game* game, char* filename)
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
			if(place != -1)
				game_set_object_location(game, place, id);
			else
				 player_setObjId(game_get_player(game), id);
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

STATUS game_save_player(Game* game, FILE * f)
{
	Player * player;
	Inventory * inv;
	Set * set;

	if(!game || !f) return ERROR;

	player = game_get_player(game);
	if(!player) return ERROR;
	fwrite(&player, player_size(), 1, f);
	inv = player_getInventory(player);
	if(!inv) return ERROR;
	fwrite(&inv, inventory_size(), 1, f);
	set = inventory_get_ids(inv);
	/*if(!set) return ERROR;
	fwrite(&set, set_size(), 1, f);*/

	return OK;
}

STATUS game_save_spaces(Game* game, FILE * f)
{
	int i;
	Space * spc;
	Set * set;

	if(!game || !f) return ERROR;

	for(i = 0; game_get_space_id_at(game, i) != NO_ID; i++){
	}
	fwrite(&i, sizeof(int), 1, f);

	for(i=0; i>=0; i--){
		spc = game_get_space(game, game_get_space_id_at(game, i));
		fwrite(&spc, space_size(), 1, f);
		set = space_get_objects_id(spc);
		/*fwrite(&set, set_size(), 1 , f);*/
	}

	return OK;
}

STATUS game_save_objects(Game * game, FILE * f)
{
	int i;
	Object * obj;

	if(!game || !f) return ERROR;

	for(i = 0; game_get_object_id_at(game, i) != NO_ID; i++){
	}
	fwrite(&i, sizeof(int), 1, f);

	for(i=0; i>=0 ; i--){
		obj = game_get_object_from_id(game, game_get_object_id_at(game, i));
		fwrite(&obj, object_size(), 1, f);

	}

	return OK;
}

STATUS game_save_links(Game * game, FILE * f)
{
	int i;
	Link * lnk;

	if(!game || !f) return ERROR;

	for(i = 0; game_get_link_id_at(game, i) != NO_ID; i++){
	}
	fwrite(&i, sizeof(int), 1, f);

	for(i=0; i>=0 ; i--){
		lnk = game_get_link(game, game_get_link_id_at(game, i));
		fwrite(&lnk, link_size(), 1, f);
	}

	link_destroy(lnk);
	return OK;
}

STATUS game_save_die(Game * game, FILE * f)
{
	Die * die;

	if(!game || !f) return ERROR;

	die = game_get_die(game);

	fwrite(&die, die_size(), 1, f);

	return OK;
}

STATUS game_save(Game * game, char * filename)
{
	FILE * save;
	char string[100];

	if(!game || !filename) return ERROR;

	sprintf(string, "saves/%s.sv", filename);

	save = fopen(string, "wb");
	if(!save) return ERROR;

	fwrite(&game, game_size(), 1, save);

	if(game_save_player(game, save) == ERROR)
		return ERROR;

	if(game_save_objects(game, save) == ERROR)
		return ERROR;

	if(game_save_spaces(game, save) == ERROR)
		return ERROR;

	if(game_save_links(game, save) == ERROR)
		return ERROR;

	if(game_save_die(game, save) == ERROR)
		return ERROR;

	fclose(save);
	return OK;
}

STATUS game_load_saved_game(Game * game, char * filename)
{
	int i;
	FILE * save;
	char string[100];
	Player * ply;
	Inventory * inv;
	Set* set;
	Object * obj;
	Space * spc;
	Link * lnk;
	Die * die;

	if(!game || !filename) return ERROR;

	sprintf(string, "saves/%s.sv", filename);

	save = fopen(string, "rb");
	if(!save) return ERROR;

	fread(&game, game_size(), 1, save);
	fread(&ply, player_size(), 1, save);
	fread(&inv, inventory_size(), 1, save);
	/*fread(&set, set_size(), 1, save);

	inventory_set_ids(inv, set);*/
	player_setInventory(ply, inv);
	game_set_player(game, ply);

	fread(&i, sizeof(int), 1, save);
	while( i >= 0){
		fread(&obj, object_size(), 1, save);
		game_set_object(game, obj);
		i--;
	}

	fread(&i, sizeof(int), 1, save);
	while( i >= 0){
		fread(&spc, space_size(), 1, save);
		/*fread(&set, set_size(), 1 ,save);
		space_set_objects_id(spc, set);*/
		game_add_space(game, spc);
	}

	fread(&i, sizeof(int), 1, save);
	while( i >= 0){
		fread(&lnk, link_size(), 1, save);
		game_set_link(game, link_getId(lnk), link_getSpace1(lnk), link_getSpace2(lnk));
	}

	fread(&die, die_size(), 1, save);
	game_set_die(game, die);

	return OK;
}
