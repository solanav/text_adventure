/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../include/game.h"
#include "../include/game_reader.h"

#define N_CALLBACK 7

struct _Game
{
	Player * player; /*!< Jugador*/
	Object * objects[MAX_OBJECTS]; /*!< Array de objetos*/
	Space * spaces[MAX_SPACES + 1]; /*!< Array de espacios*/
	Link * links[MAX_LINK]; /*!< Array de links*/
	Die * die; /*!< Dado */
	F_Command * last_cmd; /*!< ultimo comando*/
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

Game * game_create()
{
	int i;
	Game * game = NULL;

	game = (Game *) calloc(1, sizeof(Game));
	if(!game)
	{
		printf("Calloc didn't work\n");
		return NULL;
	}

	for (i = 0; i < MAX_SPACES; i++)
	{
		game->spaces[i] = NULL;
	}

	game->player = player_create("player1", NO_ID, NO_ID, 1);

	for (i =0; i < MAX_OBJECTS; i++)
	{
		game->objects[i] = NULL;
	}

	for (i = 0; i < MAX_LINK; i++)
	{
		game->links[i] = NULL;
	}

	game->die = die_ini(666);
	game_set_player_location(game, NO_ID);

	game->last_cmd = NULL;

	return game;
}

STATUS game_create_from_file(Game * game, char * filename)
{
	int i;
	Space * space_act = NULL, * space_next = NULL;
	Id space_act_id = NO_ID, space_next_id = NO_ID, link_id = NO_ID;

	if(!game || !filename) return ERROR;

	/* Load all data from file */
	if (game_load_spaces(game, filename) == ERROR) return ERROR;

	/* Put each link in the corresponding space */
	for (i=0; i<MAX_LINK; i++)
	{
		link_id = link_getId(game->links[i]);

		space_act_id = link_getSpace1(game->links[i]);
		space_next_id = link_getSpace2(game->links[i]);

		space_act = game_get_space(game, space_act_id);
		space_next = game_get_space(game, space_next_id);

		/* Este hack para hacer links es basura, ya lo cambiare - Solanav */
		if (space_act_id == space_next_id - 1) /* North <-> South */
		{
			space_set_south(space_act, link_id);
		}
		else if (space_act_id == 8 && space_next_id == 16) /* Bridge */
		{
			space_set_east(space_act, link_id);
			space_set_west(space_next, link_id);
		}
		else if (space_act_id < space_next_id) /* Oca */
		{
			space_set_east(space_act, link_id);
		}
		else if (space_act_id > space_next_id) /* Death */
		{
			space_set_east(space_act, link_id);
			space_set_west(space_act, link_id);
		}
	}

	game_set_player_location(game, game_get_space_id_at(game, 0));


	/* DEBUG */
	for (i=0; i<MAX_SPACES; i++)
	{
		space_print(game->spaces[i]);
	}

	for (i=0; i<MAX_OBJECTS; i++)
	{
		printf("Object -> %s [%ld]", object_get_name(game->objects[i]), object_get_id(game->objects[i]));
		printf("Object location -> %d", (int)game_get_object_location(game, i+1));
	}

	printf("Player name -> %s\n", player_getName(game->player));
	printf("Player location -> %ld\n", player_getLocId(game->player));
	printf("Player id -> %ld\n", player_getId(game->player));

	return OK;
}

STATUS game_destroy(Game * game)
{
	int i = 0;
	printf("\nMAX_SPACES -> %d\n", MAX_SPACES);

	for (i = 0; (i <= 26) && game->spaces[i]; i++)
	{
		printf("Iteration now on -> %d  \n", i);
		printf("Going with space -> %p  \n", (void *) game->spaces[i]);
		printf("Space ID is      -> %ld \n\n", space_get_id(game->spaces[i]));
		space_destroy(game->spaces[i]);
	}

	player_destroy(game->player);

	for(i = 0; i<MAX_OBJECTS && game->objects[i]; i++)
	{
		printf("Destroying %p with i %d\n",(void *)  game->objects[i], i);
		printf("\tObject has id %ld\n", object_get_id(game->objects[i]));
		object_destroy(game->objects[i]);
	}

	for(i = 0; i<MAX_LINK && game->links[i]; i++)
	{
		link_destroy(game->links[i]);
	}

	die_die_die(game->die);

	free(game);

	return OK;
}

Space* game_get_space(Game * game, Id id)
{
	int i;

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

	if(!game || !object_name) return NULL;

	for(i=0; i < MAX_OBJECTS && game->objects[i]; i++)
	{
		printf("Comparing [%s] with [%s]\n", object_name, object_get_name(game->objects[i]));
		if (strcasecmp(object_name, object_get_name(game->objects[i])) ==  0)
			return game->objects[i];
	}

	return NULL;
}

Object * game_get_object_from_id(Game * game, Id id)
{
	int i;

	if (id == NO_ID) return NULL;

	for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
	{
		if (id == object_get_id(game->objects[i]))
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

Id game_get_player_location(Game * game)
{
	return player_getLocId(game->player);
}

Id game_get_object_location(Game * game, Id id)
{
	int i, n;
	Set * objects = NULL;

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
		}
		set_destroy(objects);
	}
	return NO_ID;
}

STATUS game_update(Game * game, F_Command * cmd)
{
	if(!game || !cmd) return ERROR;

	game->last_cmd = cmd;

	(*game_callback_fn_list[command_getCmd(cmd)])(game);
	return OK;
}

F_Command * game_get_last_command(Game * game)
{
	return game->last_cmd;
}

T_Command game_get_last_command_text(Game * game)
{
	return command_getCmd(game->last_cmd);
}

void game_print_data(Game * game)
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

BOOL game_is_over(Game * game)
{
	return FALSE;
}

void game_callback_unknown(Game * game)
{
}

void game_callback_exit(Game * game)
{
}

void game_callback_pickup(Game * game)
{
	/* TODO : check if the object exists (same for drop) */
	int i = 0;
	Id debug = 0;

	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space * space_pointer = game_get_space(game, player_locId);
	char object[20] = {0};

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

void game_callback_drop(Game * game)
{
	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space * space_pointer = game_get_space(game, player_locId);
	char object[20] = {0};

	if (!game) return;

	strcpy(object, command_get_id(game->last_cmd));
	object_id = object_get_id(game_get_object(game, object));

	if (object_id > MAX_OBJECTS) return;

	if(player_removeObjId(game->player, object_id) == ERROR) return;

	space_add_object(space_pointer, object_id);
	player_removeObjId(game->player, object_id);

	return;
}

void game_callback_roll(Game * game)
{
	die_roll(game->die);
	die_print(stdout, game->die);
	return;
}

void game_callback_move(Game * game)
{
	Id link_id = NO_ID;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	char movement[20] = {0};

	space_id = game_get_player_location(game);
	strcpy(movement, command_get_id(game->last_cmd));

	printf("Someone is trying to move...\n\tPlayer loc -> %ld\n\tMovement -> %s\n", space_id, movement);

	if (!game || space_id == NO_ID) return;

	if (strcmp(movement, "north") == 0)
	{
		link_id = space_get_north(game_get_space(game, space_id));
		current_id = link_getSpace1(game_get_link(game, link_id));
	}
	else if (strcmp(movement, "east") == 0)
	{
		link_id = space_get_east(game_get_space(game, space_id));
		current_id = link_getSpace2(game_get_link(game, link_id));
	}
	else if (strcmp(movement, "south") == 0)
	{
		link_id = space_get_south(game_get_space(game, space_id));
		current_id = link_getSpace2(game_get_link(game, link_id));
	}
	else if (strcmp(movement, "west") == 0)
	{
		link_id = space_get_west(game_get_space(game, space_id));
		current_id = link_getSpace1(game_get_link(game, link_id));
	}
	else
	{
		return;
	}

	printf("Id of link you are trying to use -> %ld\n", link_id);
	printf("\tId of actposition -> %ld\n", link_getSpace1(game_get_link(game, link_id)));
	printf("\tId of destination -> %ld\n", link_getSpace2(game_get_link(game, link_id)));

	if(current_id != NO_ID)
		game_set_player_location(game, current_id);

	printf("Player's new location -> %ld\n", game_get_player_location(game));

}

void game_callback_check(Game * game)
{
	char object_description[20] = {0};
	char object_name[20] = {0};

	char space_description[20] = {0};
	char space_name[20] = {0};

	if (!game) return;

	/* Clever hack if i say so myself, prob shouldn't be doing it but meh - Solanav */
	if (strcasecmp(command_get_id(game->last_cmd), "s") == 0 || strcasecmp(command_get_id(game->last_cmd), "space") == 0)
	{
		strcpy(space_name, command_get_id(game->last_cmd));
		strcpy(space_description, space_get_description(game_get_space(game, player_getLocId(game->player))));

		command_set_id(game->last_cmd, space_description);
	}
	else
	{
		strcpy(object_name, command_get_id(game->last_cmd));

		if (!game_get_object(game, object_name)) return;

		strcpy(object_description, object_get_description(game_get_object(game, object_name)));

		command_set_id(game->last_cmd, object_description);
	}

	return;
}

STATUS game_add_space(Game * game, Space* space)
{
	int i = 0;

	if (space == NULL) return ERROR;

	while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
		i++;

	if (i >= MAX_SPACES) return ERROR;

	game->spaces[i] = space;

	return OK;
}

Id game_get_space_id_at(Game * game, int position)
{
	if (position < 0 || position >= MAX_SPACES) return NO_ID;

	return space_get_id(game->spaces[position]);
}

STATUS game_set_player_location(Game * game, Id id)
{
	if (id == NO_ID) return ERROR;

	player_setLocId(game->player, id);

	return OK;
}

Id game_get_object_id_at(Game * game, int position)
{
	if (position < 0 || position >= MAX_OBJECTS) return NO_ID;

	return object_get_id(game->objects[position]);
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
			return OK;
		}
	}

	return ERROR;
}

STATUS game_set_object(Game* game, Object* object)
{
	int i;

	if(!game || !object) return ERROR;

	for (i = 0; i < MAX_OBJECTS; i++)
	{
		if (game_get_object_id_at(game, i) == NO_ID)
		{
			game->objects[i] = object;
			return OK;
		}
	}

	return OK;
}

STATUS game_set_object_location(Game * game, Id id, Id obj_id)
{
	int i;

	if (id == NO_ID || !game) return ERROR;

	printf("Somebody is trying to set %ld to %ld\n", obj_id, id);
	for (i = 0; i < MAX_SPACES; i++)
	{
		if (space_get_id(game->spaces[i]) == id)
		{
			printf("It worked\n");
			if(space_add_object(game->spaces[i], obj_id) == ERROR)
				printf("This didnt work for some reason %ld\n", obj_id);
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
