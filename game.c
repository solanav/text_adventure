/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_reader.h"

#define N_CALLBACK 8

struct _Game
{
	Player * player;
	Object * objects[MAX_OBJECTS];
	Space * spaces[MAX_SPACES + 1];
	Link * links[MAX_LINK];
	Die * die;
	F_Command * last_cmd;
};

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game * game);
void game_callback_exit(Game * game);
void game_callback_pickup(Game * game);
void game_callback_drop(Game * game);
void game_callback_roll(Game * game);
void game_callback_move(Game * game);
void game_callback_check(Game * game);

static callback_fn game_callback_fn_list[N_CALLBACK]=
{
	game_callback_unknown,
	game_callback_exit,
	game_callback_pickup,
	game_callback_drop,
	game_callback_roll,
	game_callback_move,
	game_callback_check
};

/**
   Game interface implementation
*/

STATUS game_create(Game* game)
{
	/*
	* Fill game structure with empty values
	*
	* game: the main game structure
	*
	* returns: ERROR or OK
	*/
	int i;
	char name[20];

	for (i = 0; i < MAX_SPACES; i++) {
		game->spaces[i] = NULL;
	}

	for (i = 0; i < MAX_LINK; i++) {
		game->links[i] = NULL;
	}

	game->player = player_create("player1", NO_ID, NO_ID, 1);

	for(i = 0; i < 4; i++)
	{
		sprintf(name, "o%d", i+1);
		game->objects[i] = object_create(name, (long int) i+1);
	}

	game->die = die_ini(666);
	game_set_player_location(game, NO_ID);

	game->last_cmd = command_create(NO_CMD, NO_ID);

	return OK;
}

STATUS game_create_from_file(Game* game, char* filename)
{
	/* Create game */
	if (game_create(game) == ERROR) return ERROR;

	/* Load provided file */
	if (game_load_spaces(game, filename) == ERROR) return ERROR;

	game_set_player_location(game, game_get_space_id_at(game, 0));

	return OK;
}

STATUS game_destroy(Game* game)
{
	int i = 0;
	printf("\nMAX_SPACES -> %d\n", MAX_SPACES);

	for (i = 0; (i <= 26) && (game->spaces[i]); i++)
	{
		printf("Iteration now on -> %d  \n", i);
		printf("Going with space -> %p  \n", (void *) game->spaces[i]);
		printf("Space ID is      -> %ld \n\n", space_get_id(game->spaces[i]));
		space_destroy(game->spaces[i]);
	}

	player_destroy(game->player);

	for(i = 0; i<MAX_OBJECTS; i++)
	{
		printf("Destroying %p with i %d\n",(void *)  game->objects[i], i);
		printf("\tObject has id %ld\n", object_get_id(game->objects[i]));
		object_destroy(game->objects[i]);
	}

	die_die_die(game->die);

	return OK;
}

Space* game_get_space(Game* game, Id id)
{
	int i = 0;

	if (id == NO_ID) return NULL;

	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		if (id == space_get_id(game->spaces[i]))
			return game->spaces[i];
	}

	return NULL;
}

Player* game_get_player(Game * game)
{
	if(!game) return NULL;

	return game->player;
}

Object * game_get_object(Game * game, char * object_name)
{
	int i;

	if(!game || object_name == NULL) return NULL;

	for(i=0; i < MAX_LINK && game->links[i]; i++)
	{
		/* Si quieres que tenga en cuenta mayus cambiar por strcmp*/
		if (strcasecmp(object_name, object_get_name(game->objects[i])) ==  0)
			return game->objects[i];
	}

	return NULL;
}

Link * game_get_link(Game * game, Id id)
{
	int i;

	if(!game || id == NO_ID) return NULL;

	for(i=0; i < MAX_LINK && game->links[i]; i++)
	{
		if (id == link_getId(game->links[i]))
			return game->links[i];
	}

	return NULL;
}

Id game_get_link_id_at(Game * game, int pos)
{
	if(!game || pos == -1) return NO_ID;

	return link_getId(game->links[pos]);
}

Id game_get_player_location(Game* game)
{
	return player_getLocId(game->player);
}

Id game_get_object_location(Game* game, Id id)
{
	int i, n;
	Set* objects;

	if (!game) return NO_ID;

	/* Itera por los espacios comprobando si esta el objeto que buscas*/
	for (i = 0; i < MAX_SPACES; i++)
	{
		objects = space_get_objects_id(game->spaces[i]);
		for(n = 0; set_get_id(objects, n) != NO_ID; n++)
		{
			if (set_get_id(objects, n) == id)
			{
				set_destroy(objects);
				return space_get_id(game->spaces[i]);
			}
			set_destroy(objects);
		}
	}
	return NO_ID;
}

STATUS game_update(Game* game, F_Command * cmd)
{
	if(!game || !cmd) return ERROR;

	game->last_cmd = cmd;

	(*game_callback_fn_list[command_getCmd(cmd)])(game);
	return OK;
}

F_Command * game_get_last_command(Game* game)
{
	return game->last_cmd;
}

T_Command game_get_last_command_text(Game * game)
{
	return command_getCmd(game->last_cmd);
}

void game_print_data(Game* game)
{
	int i = 0;

	printf("\n\n-------------\n\n");

	printf("=> Spaces: \n");
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
	space_print(game->spaces[i]);
	}

	/* TODO : lo mismo de graphic engine, hay que hacer print de mas de un ID de objeto ahora uso 1*/
	printf("=> Object location: %d\n", (int) game_get_object_location(game, 1));
	printf("=> Player location: %d\n", (int) game_get_player_location(game));
	printf("prompt:> ");
}

BOOL game_is_over(Game* game)
{
	return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game)
{
}

void game_callback_exit(Game* game)
{
}

void game_callback_pickup(Game* game)
{
	/* TODO : check if the object exists (same for drop) */
	int i = 0;
	Id debug = 0;

	Id player_locId = game_get_player_location(game);
	Id object_id;
	Space * space_pointer = game_get_space(game, player_locId);
	char object[20];

	strcpy(object, command_get_id(game->last_cmd));
	object_id = object_get_id(game_get_object(game, object));

	if (!game) return;
	if (game_get_object_location(game, object_id) == game_get_player_location(game))
	{
		player_setObjId(game->player, object_id);
		space_remove_object(space_pointer, object_id);
	}

	/* DEBUG : this is to check if it works (spoiler alert: it does)*/
	printf("ThiS niBBa has the following objects:\n");
	for (i=1; debug != NO_ID && i<10; i++)
	{
		debug = player_getObjId(game->player, i);
		printf("\tTHIS ONE -> %ld [%d]\n", debug, i);
	}

	return;
}

void game_callback_drop(Game* game)
{
	Id player_locId = game_get_player_location(game);
	Id object_id;
	Space * space_pointer = game_get_space(game, player_locId);
	char object[20];

	strcpy(object, command_get_id(game->last_cmd));
	object_id = object_get_id(game_get_object(game, object));

	if (!game) return;

	if (object_id > MAX_OBJECTS) return;

	space_add_object(space_pointer, object_id);
	player_removeObjId(game->player, object_id);
	return;
}

void game_callback_roll(Game* game)
{
	die_roll(game->die);
	die_print(stdout, game->die);
	return;
}

void game_callback_move(Game* game)
{
	Id link_id = NO_ID;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	char movement[20];

	space_id = game_get_player_location(game);
	strcpy(movement, command_get_id(game->last_cmd));

	printf("Trying to move to %s\n", movement);
	if (NO_ID == space_id) return;

	link_id = space_get_id(game_get_space(game, space_id));

	if (strcmp(movement, "north") == 0)
	{
		current_id = link_getSpace2(game_get_link(game, link_id));
		printf("Moving from %ld to %ld\n", link_getSpace1(game_get_link(game, link_id)), link_getSpace2(game_get_link(game, link_id)));
		if(current_id != NO_ID)
			game_set_player_location(game, current_id);
	}
	else if (strcmp(movement, "east") == 0)
	{
		current_id = link_getSpace2(game_get_link(game, link_id));
		printf("Moving from %ld to %ld\n", link_getSpace1(game_get_link(game, link_id)), link_getSpace2(game_get_link(game, link_id)));
		if(current_id != NO_ID)
			game_set_player_location(game, current_id);
	}
	else if (strcmp(movement, "south") == 0)
	{
		current_id = link_getSpace2(game_get_link(game, link_id));
		printf("Moving from %ld to %ld\n", link_getSpace1(game_get_link(game, link_id)), link_getSpace2(game_get_link(game, link_id)));
		if(current_id != NO_ID)
			game_set_player_location(game, current_id);
	}
	else if (strcmp(movement, "west") == 0)
	{
		current_id = link_getSpace2(game_get_link(game, link_id));
		printf("Moving from %ld to %ld\n", link_getSpace1(game_get_link(game, link_id)), link_getSpace2(game_get_link(game, link_id)));
		if(current_id != NO_ID)
			game_set_player_location(game, current_id);
	}
	else
	{
		return;
	}

}

void game_callback_check(Game* game)
{
}

STATUS game_add_space(Game* game, Space* space)
{
	int i = 0;

	if (space == NULL) return ERROR;

	while ( (i < MAX_SPACES) && (game->spaces[i] != NULL))
		i++;

	if (i >= MAX_SPACES) return ERROR;

	game->spaces[i] = space;

	return OK;
}

Id game_get_space_id_at(Game* game, int position)
{
	if (position < 0 || position >= MAX_SPACES) return NO_ID;

	return space_get_id(game->spaces[position]);
}

STATUS game_set_player_location(Game* game, Id id)
{
	/*
	* Sets player location to "id"
	*
	* game: the main game structure
	* id: new location for player
	*
	* returns: ERROR or OK
	*/

	if (id == NO_ID) return ERROR;

	player_setLocId(game->player, id);

	return OK;
}

STATUS game_set_link(Game * game, Id link_id, Id space_id0, Id space_id1)
{
	int i;
	
	if (link_id == NO_ID || space_id0 == NO_ID || space_id1 == NO_ID || !game ) return ERROR;
	
	for (i = 0; i < MAX_LINK; i++)
	{
		if (game_get_link_id_at(game, i) == NO_ID)
		{
			game->links[i] = link_create(link_id);
			link_setSpaces(game->links[i], space_id0, space_id1);
			printf("Good, we got that id and now is -> %ld\n", game_get_link_id_at(game, i));
			return OK;
		}
	}

	return ERROR;
}

STATUS game_set_object_location(Game* game, Id id, Id obj_id)
{
	/*
	* Sets object location to "id"
	*
	* game: the main game structure
	* id: new location for object
	*
	* returns: ERROR or OK
	*/

	int i;

	if (id == NO_ID || !game) return ERROR;

	for (i = 0; i < MAX_SPACES; i++)
	{
		if (space_get_id(game->spaces[i]) == id)
		{
			space_add_object(game->spaces[i], obj_id);
			return OK;
		}
	}

	return ERROR;
}

int game_get_last_roll(Game * game)
{
	if(!game) return -1;

	return die_get_last_roll(game->die);
}

BOOL game_areSpacesAdjacent(Game * g, Id space1, Id space2)
{
	if(!g || space1 == NO_ID || space2 == NO_ID) return FALSE;


	if(space_get_north(game_get_space(g, space2)) == space1)
		return TRUE;
	else if(space_get_east(game_get_space(g, space2)) == space1)
		return TRUE;
	else if(space_get_south(game_get_space(g, space2)) == space1)
		return TRUE;
	else if(space_get_west(game_get_space(g, space2)) == space1)
		return TRUE;

	return FALSE;
}
