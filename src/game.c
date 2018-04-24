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
void game_callbackUnknown(Game * game);
void game_callbackExit(Game * game);
void game_callbackPickup(Game * game);
void game_callbackDrop(Game * game);
void game_callbackRoll(Game * game);
void game_callbackMove(Game * game);
void game_callbackCheck(Game * game);

static callback_fn game_callback_fn_list[N_CALLBACK]=
{
	game_callbackUnknown,
	game_callbackExit,
	game_callbackPickup,
	game_callbackDrop,
	game_callbackRoll,
	game_callbackMove,
	game_callbackCheck
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

	game->objects[0] = object_create("linterna", (long int) 1);
	game->objects[1] = object_create("libro", (long int) 2);
	game->objects[2] = object_create("pocion", (long int) 3);
	game->objects[3] = object_create("llave", (long int) 4);

	for (i = 0; i < MAX_LINK; i++)
	{
		game->links[i] = NULL;
	}

	game->die = die_ini(666);
	game_setPlayerLocation(game, NO_ID);

	game->last_cmd = NULL;

	return game;
}

STATUS game_createFromFile(Game * game, char * filename)
{
	int i;
	Space * space_act = NULL, * space_next = NULL;
	Id space_act_id = NO_ID, space_next_id = NO_ID, link_id = NO_ID;

	if(!game || !filename) return ERROR;

	/* Load all data from file */
	if (game_loadAll(game, filename) == ERROR) return ERROR;

	/* Put each link in the corresponding space */
	for (i=0; i<MAX_LINK; i++)
	{
		link_id = link_getId(game->links[i]);

		space_act_id = link_getSpace1(game->links[i]);
		space_next_id = link_getSpace2(game->links[i]);

		space_act = game_getSpace(game, space_act_id);
		space_next = game_getSpace(game, space_next_id);

		/* Este hack para hacer links es basura, ya lo cambiare - Solanav */
		if (space_act_id == space_next_id - 1) /* North <-> South */
		{
			space_setSouth(space_act, link_id);
		}
		else if (space_act_id == 8 && space_next_id == 16) /* Bridge */
		{
			space_setEast(space_act, link_id);
			space_setWest(space_next, link_id);
		}
		else if (space_act_id < space_next_id) /* Oca */
		{
			space_setEast(space_act, link_id);
		}
		else if (space_act_id > space_next_id) /* Death */
		{
			space_setEast(space_act, link_id);
			space_setWest(space_act, link_id);
		}
	}

	game_setPlayerLocation(game, game_getSpaceIdAt(game, 0));


	/* DEBUG */
	for (i=0; i<MAX_SPACES; i++)
	{
		space_print(game->spaces[i]);
	}

	for (i=0; i<MAX_OBJECTS; i++)
	{
		printf("Object -> %s [%ld]", object_getName(game->objects[i]), object_getId(game->objects[i]));
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
		printf("Space ID is      -> %ld \n\n", space_getId(game->spaces[i]));
		space_destroy(game->spaces[i]);
	}

	player_destroy(game->player);

	for(i = 0; i<MAX_OBJECTS && game->objects[i]; i++)
	{
		printf("Destroying %p with i %d\n",(void *)  game->objects[i], i);
		printf("\tObject has id %ld\n", object_getId(game->objects[i]));
		object_destroy(game->objects[i]);
	}

	for(i = 0; i<MAX_LINK && game->links[i]; i++)
	{
		link_destroy(game->links[i]);
	}

	die_dieDie(game->die);

	free(game);

	return OK;
}

Space* game_getSpace(Game * game, Id id)
{
	int i;

	if (id == NO_ID) return NULL;

	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		if (id == space_getId(game->spaces[i]))
			return game->spaces[i];
	}

	return NULL;
}

Player* game_getPlayer(Game * game)
{
	if(!game) return NULL;

	return game->player;
}

Object * game_getObject(Game * game, char * object_name)
{
	int i;

	if(!game || !object_name) return NULL;

	for(i=0; i < 4 && game->objects[i]; i++)
	{
		printf("Comparing [%s] with [%s]\n", object_name, object_getName(game->objects[i]));
		if (strcasecmp(object_name, object_getName(game->objects[i])) ==  0)
			return game->objects[i];
	}

	return NULL;
}

Object * game_getObjectFromId(Game * game, Id id)
{
	int i;

	if (id == NO_ID) return NULL;

	for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
	{
		if (id == object_getId(game->objects[i]))
			return game->objects[i];
	}

	return NULL;
}

Link * game_getLink(Game * game, Id id)
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

Id game_getLinkIdAt(Game * game, int pos)
{
	if(!game || pos == -1) return NO_ID;

	return link_getId(game->links[pos]);
}

Id game_getPlayerLocation(Game * game)
{
	return player_getLocId(game->player);
}

Id game_getObjectLocation(Game * game, Id id)
{
	int i, n;
	Set * objects = NULL;

	/* Itera por los espacios comprobando si esta el objeto que buscas*/
	for (i = 0; i < MAX_SPACES; i++)
	{
		objects = space_getObjectsId(game->spaces[i]);
		for(n = 0; set_getId(objects, n) != NO_ID; n++)
		{
			if (set_getId(objects, n) == id)
			{
				set_destroy(objects);
				return space_getId(game->spaces[i]);
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

F_Command * game_getLastCommand(Game * game)
{
	return game->last_cmd;
}

T_Command game_getLastCommandText(Game * game)
{
	return command_getCmd(game->last_cmd);
}

void game_printData(Game * game)
{
	int i = 0;

	printf("\n\n-------------\n\n");

	printf("=> Spaces: \n");
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
	space_print(game->spaces[i]);
	}

	/* TODO : lo mismo de graphic engine, hay que hacer print de mas de un ID de objeto ahora uso 1*/
	printf("=> Object location: %d\n", (int) game_getObjectLocation(game, 1));
	printf("=> Player location: %d\n", (int) game_getPlayerLocation(game));
	printf("prompt:> ");
}

BOOL game_isOver(Game * game)
{
	return FALSE;
}

void game_callbackUnknown(Game * game)
{
}

void game_callbackExit(Game * game)
{
}

void game_callbackPickup(Game * game)
{
	/* TODO : check if the object exists (same for drop) */
	int i = 0;
	Id debug = 0;

	Id player_locId = game_getPlayerLocation(game);
	Id object_id = NO_ID;
	Space * space_pointer = game_getSpace(game, player_locId);
	char object[20] = {0};

	strcpy(object, command_getId(game->last_cmd));
	object_id = object_getId(game_getObject(game, object));

	if (!game) return;
	if (game_getObjectLocation(game, object_id) == game_getPlayerLocation(game))
	{
		player_setObjId(game->player, object_id);
		space_removeObject(space_pointer, object_id);
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

void game_callbackDrop(Game * game)
{
	Id player_locId = game_getPlayerLocation(game);
	Id object_id = NO_ID;
	Space * space_pointer = game_getSpace(game, player_locId);
	char object[20] = {0};

	if (!game) return;

	strcpy(object, command_getId(game->last_cmd));
	object_id = object_getId(game_getObject(game, object));

	if (object_id > MAX_OBJECTS) return;

	space_addObject(space_pointer, object_id);
	player_removeObjId(game->player, object_id);

	return;
}

void game_callbackRoll(Game * game)
{
	die_roll(game->die);
	die_print(stdout, game->die);
	return;
}

void game_callbackMove(Game * game)
{
	Id link_id = NO_ID;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	char movement[20] = {0};

	space_id = game_getPlayerLocation(game);
	strcpy(movement, command_getId(game->last_cmd));

	printf("Someone is trying to move...\n\tPlayer loc -> %ld\n\tMovement -> %s\n", space_id, movement);

	if (!game || space_id == NO_ID) return;

	if (strcmp(movement, "north") == 0)
	{
		link_id = space_getNorth(game_getSpace(game, space_id));
		current_id = link_getSpace1(game_getLink(game, link_id));
	}
	else if (strcmp(movement, "east") == 0)
	{
		link_id = space_getEast(game_getSpace(game, space_id));
		current_id = link_getSpace2(game_getLink(game, link_id));
	}
	else if (strcmp(movement, "south") == 0)
	{
		link_id = space_getSouth(game_getSpace(game, space_id));
		current_id = link_getSpace2(game_getLink(game, link_id));
	}
	else if (strcmp(movement, "west") == 0)
	{
		link_id = space_getWest(game_getSpace(game, space_id));
		current_id = link_getSpace1(game_getLink(game, link_id));
	}
	else
	{
		return;
	}

	printf("Id of link you are trying to use -> %ld\n", link_id);
	printf("\tId of actposition -> %ld\n", link_getSpace1(game_getLink(game, link_id)));
	printf("\tId of destination -> %ld\n", link_getSpace2(game_getLink(game, link_id)));

	if(current_id != NO_ID)
		game_setPlayerLocation(game, current_id);

	printf("Player's new location -> %ld\n", game_getPlayerLocation(game));

}

void game_callbackCheck(Game * game)
{
	char object_description[20] = {0};
	char object_name[20] = {0};

	char space_description[20] = {0};
	char space_name[20] = {0};

	if (!game) return;

	/* Clever hack if i say so myself, prob shouldn't be doing it but meh - Solanav */
	if (strcasecmp(command_getId(game->last_cmd), "s") == 0 || strcasecmp(command_getId(game->last_cmd), "space") == 0)
	{
		strcpy(space_name, command_getId(game->last_cmd));
		strcpy(space_description, space_getDescription(game_getSpace(game, player_getLocId(game->player))));

		command_setId(game->last_cmd, space_description);
	}
	else
	{
		strcpy(object_name, command_getId(game->last_cmd));

		if (!game_getObject(game, object_name)) return;

		strcpy(object_description, object_getDescription(game_getObject(game, object_name)));

		command_setId(game->last_cmd, object_description);
	}

	return;
}

STATUS game_addSpace(Game * game, Space* space)
{
	int i = 0;

	if (space == NULL) return ERROR;

	while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
		i++;

	if (i >= MAX_SPACES) return ERROR;

	game->spaces[i] = space;

	return OK;
}

Id game_getSpaceIdAt(Game * game, int position)
{
	if (position < 0 || position >= MAX_SPACES) return NO_ID;

	return space_getId(game->spaces[position]);
}

STATUS game_setPlayerLocation(Game * game, Id id)
{
	if (id == NO_ID) return ERROR;

	player_setLocId(game->player, id);

	return OK;
}

STATUS game_setLink(Game * game, Id link_id, Id space_id0, Id space_id1)
{
	int i;

	if (link_id == NO_ID || space_id0 == NO_ID || space_id1 == NO_ID || !game ) return ERROR;

	for (i = 0; i < MAX_LINK; i++)
	{
		if (game_getLinkIdAt(game, i) == NO_ID)
		{
			game->links[i] = link_create(link_id);
			link_setSpaces(game->links[i], space_id0, space_id1);
			return OK;
		}
	}

	return ERROR;
}

STATUS game_setObjectLocation(Game * game, Id id, Id obj_id, char * name, char * description)
{
	int i;

	if (id == NO_ID || !game) return ERROR;

	for (i = 0; i < MAX_SPACES; i++)
	{
		if (space_getId(game->spaces[i]) == id)
		{
			space_addObject(game->spaces[i], obj_id);
			object_setDescription(game_getObject(game, name), description);
			return OK;
		}
	}

	return ERROR;
}

int game_getLastRoll(Game * game)
{
	if(!game) return -1;

	return die_getLastRoll(game->die);
}

BOOL game_areSpacesAdjacent(Game * g, Id space1, Id space2)
{
	if(!g || space1 == NO_ID || space2 == NO_ID) return FALSE;


	if(space_getNorth(game_getSpace(g, space2)) == space1)
		return TRUE;
	else if(space_getEast(game_getSpace(g, space2)) == space1)
		return TRUE;
	else if(space_getSouth(game_getSpace(g, space2)) == space1)
		return TRUE;
	else if(space_getWest(game_getSpace(g, space2)) == space1)
		return TRUE;

	return FALSE;
}
