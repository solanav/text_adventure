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
#include "../include/sprite_loader.h"
#include "../include/sprite.h"

#define N_CALLBACK 11

struct _Game
{
	Player *player;		       /*!< Jugador*/
	Object *objects[MAX_OBJECTS];  /*!< Array de objetos*/
	Space *spaces[MAX_SPACES + 1]; /*!< Array de espacios*/
	Link *links[MAX_LINK];	 /*!< Array de links*/
	Die *die;		       /*!< Dado */
	F_Command *last_cmd;	   /*!< ultimo comando*/
	Sprite *sprites[MAX_SPRITES];  /*!< sprites del mapa*/
};

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game *game);
void game_callback_exit(Game *game);
void game_callback_pickup(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_move(Game *game);
void game_callback_check(Game *game);
void game_callback_turnOn(Game *game);
void game_callback_turnOff(Game *game);
void game_callback_open(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] =
    {
	game_callback_unknown,
	game_callback_exit,
	game_callback_pickup,
	game_callback_drop,
	game_callback_roll,
	game_callback_move,
	game_callback_check,
	game_callback_turnOn,
	game_callback_turnOff,
	game_callback_open};

Game *game_create()
{
	int i;
	Game *game = NULL;

	game = (Game *)calloc(1, sizeof(Game));
	if (!game)
	{
		printf("Calloc didn't work\n");
		return NULL;
	}

	for (i = 0; i < MAX_SPACES; i++)
	{
		game->spaces[i] = NULL;
	}

	game->player = player_create("player1", NO_ID, NO_ID, 1);

	game->objects[0] = object_create("linterna", (long int)1);
	game->objects[1] = object_create("libro", (long int)2);
	game->objects[2] = object_create("pocion", (long int)3);
	game->objects[3] = object_create("llave", (long int)4);

	for (i = 0; i < MAX_LINK; i++)
	{
		game->links[i] = NULL;
	}

	for (i = 0; i < MAX_SPRITES; i++)
	{
		game->sprites[i] = NULL;
	}

	game->die = die_ini(666);
	game_set_player_location(game, NO_ID);

	game->last_cmd = NULL;

	return game;
}

STATUS game_create_from_file(Game *game, char *filename)
{
	int i;
	Space *space_act = NULL;
	Id space_act_id = NO_ID, link_id = NO_ID;
	int direction;

	if (!game || !filename)
		return ERROR;

	/* Load all opened_links from file */
	if (game_load_spaces(game, filename) == ERROR)
		return ERROR;

	/* Load all sprites */
	if (sprite_loader_map(game, "data/map.dat") == ERROR)
		return ERROR;

	for (i = 0; game->sprites[i]; i++)
	{
		sprite_print(game->sprites[i]);
	}

	/* Put each link in the corresponding space */
	for (i = 0; i < MAX_LINK; i++)
	{
		link_id = link_getId(game->links[i]);

		if (link_id == -1)
			continue;

		space_act_id = link_getSpace1(game->links[i]);

		space_act = game_get_space(game, space_act_id);

		direction = link_getDirection(game_get_link(game, link_id));

		if (direction == 0)
			space_set_north(space_act, link_id);
		else if (direction == 1)
			space_set_east(space_act, link_id);
		else if (direction == 2)
			space_set_south(space_act, link_id);
		else if (direction == 3)
			space_set_west(space_act, link_id);
	}

	game_set_player_location(game, game_get_space_id_at(game, 0));

	update_sprites(game);

	return OK;
}

STATUS game_destroy(Game *game)
{
	int i = 0;
	printf("\nMAX_SPACES -> %d\n", MAX_SPACES);

	for (i = 0; i <= MAX_SPACES && game->spaces[i]; i++)
		space_destroy(game->spaces[i]);

	player_destroy(game->player);

	for (i = 0; i < MAX_OBJECTS && game->objects[i]; i++)
		object_destroy(game->objects[i]);

	for (i = 0; i < MAX_LINK && game->links[i]; i++)
		link_destroy(game->links[i]);

	for (i = 0; i < MAX_SPRITES && game->sprites[i]; i++)
		sprite_destroy(game->sprites[i]);

	die_die_die(game->die);

	free(game);

	return OK;
}

Space *game_get_space(Game *game, Id id)
{
	int i;

	if (id == NO_ID)
		return NULL;

	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		if (id == space_get_id(game->spaces[i]))
			return game->spaces[i];
	}

	return NULL;
}

Player *game_get_player(Game *game)
{
	if (!game)
		return NULL;

	return game->player;
}

Object *game_get_object(Game *game, char *object_name)
{
	int i;

	if (!game || !object_name)
		return NULL;

	for (i = 0; i < 4 && game->objects[i]; i++)
	{
		if (strcasecmp(object_name, object_get_name(game->objects[i])) == 0)
			return game->objects[i];
	}

	return NULL;
}

Object *game_get_object_from_id(Game *game, Id id)
{
	int i;

	if (id == NO_ID)
		return NULL;

	for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
	{
		if (id == object_get_id(game->objects[i]))
			return game->objects[i];
	}

	return NULL;
}

Link *game_get_link(Game *game, Id id)
{
	int i;

	if (!game || id == NO_ID)
		return NULL;

	for (i = 0; i < MAX_LINK && game->links[i]; i++)
	{
		if (id == link_getId(game->links[i]))
			return game->links[i];
	}

	return NULL;
}

Id game_get_link_id_at(Game *game, int pos)
{
	if (!game || pos == -1)
		return NO_ID;

	return link_getId(game->links[pos]);
}

Id game_get_player_location(Game *game)
{
	return player_getLocId(game->player);
}

Id game_get_object_location(Game *game, Id id)
{
	int i, n;
	Set *objects = NULL;

	/* Itera por los espacios comprobando si esta el objeto que buscas*/
	for (i = 0; i < MAX_SPACES; i++)
	{
		objects = space_get_objects_id(game->spaces[i]);
		for (n = 0; set_get_id(objects, n) != NO_ID; n++)
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

STATUS game_update(Game *game, F_Command *cmd)
{
	if (!game || !cmd)
		return ERROR;

	game->last_cmd = cmd;

	printf("Updating with command -> %d\n\n", command_getCmd(cmd));

	(*game_callback_fn_list[command_getCmd(cmd)])(game);
	return OK;
}

F_Command *game_get_last_command(Game *game)
{
	return game->last_cmd;
}

T_Command game_get_last_command_text(Game *game)
{
	return command_getCmd(game->last_cmd);
}

void game_print_opened_links(Game *game)
{
	int i = 0;

	printf("\n\n-------------\n\n");

	printf("=> Spaces: \n");
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		space_print(game->spaces[i]);
	}

	/* TODO : print more objects*/
	printf("=> Object location: %d\n", (int)game_get_object_location(game, 1));
	printf("=> Player location: %d\n", (int)game_get_player_location(game));
	printf("prompt:> ");
}

STATUS game_add_space(Game *game, Space *space)
{
	int i = 0;

	if (space == NULL)
		return ERROR;

	while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
		i++;

	if (i >= MAX_SPACES)
		return ERROR;

	game->spaces[i] = space;

	return OK;
}

Sprite *game_get_sprite(Game *game, Id id)
{
	int i;

	if (!game || id == NO_ID)
		return NULL;

	for (i = 0; i < MAX_SPRITES; i++)
	{
		printf("Checking -> %d has id -> %ld\n", i, sprite_getId(game->sprites[i]));
		if (sprite_getId(game->sprites[i]) == id)
		{
			return game->sprites[i];
		}
	}
	return NULL;
}

STATUS game_add_sprite(Game *game, Sprite *sprite, int i)
{
	game->sprites[i] = sprite;

	printf("Someone added this [%d] ->\n", i);

	return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
	if (position < 0 || position >= MAX_SPACES)
		return NO_ID;

	return space_get_id(game->spaces[position]);
}

STATUS game_set_player_location(Game *game, Id id)
{
	if (id == NO_ID)
		return ERROR;

	player_setLocId(game->player, id);

	return OK;
}

STATUS game_set_link(Game *game, Id link_id, Id space_id0, Id space_id1, int direction)
{
	int i;

	if (link_id == NO_ID || space_id0 == NO_ID || space_id1 == NO_ID || !game || direction == -1)
		return ERROR;

	/* Loop to search for next NO_ID */
	for (i = 0; i < MAX_LINK; i++)
	{
		if (game_get_link_id_at(game, i) == NO_ID)
		{
			game->links[i] = link_create(link_id);
			link_setSpaces(game->links[i], space_id0, space_id1);
			link_setDirection(game->links[i], direction);
			return OK;
		}
	}

	return ERROR;
}

STATUS game_set_object_location(Game *game, Id id, Id obj_id, char *name, char *description)
{
	int i;

	if (id == NO_ID || !game)
		return ERROR;

	for (i = 0; i < MAX_SPACES; i++)
	{
		if (space_get_id(game->spaces[i]) == id)
		{
			space_add_object(game->spaces[i], obj_id);
			object_set_description(game_get_object(game, name), description);
			return OK;
		}
	}

	return ERROR;
}

int game_get_last_roll(Game *game)
{
	if (!game)
		return -1;

	return die_get_last_roll(game->die);
}

BOOL game_areSpacesAdjacent(Game *g, Id space1, Id space2)
{
	if (!g || space1 == NO_ID || space2 == NO_ID)
		return FALSE;

	if (space_get_north(game_get_space(g, space2)) == space1)
		return TRUE;
	else if (space_get_east(game_get_space(g, space2)) == space1)
		return TRUE;
	else if (space_get_south(game_get_space(g, space2)) == space1)
		return TRUE;
	else if (space_get_west(game_get_space(g, space2)) == space1)
		return TRUE;

	return FALSE;
}

STATUS update_sprites(Game *game)
{
	int i;

	Link *north = NULL, *east = NULL, *south = NULL, *west = NULL;
	BOOL light = FALSE;
	Space *space = NULL;

	int opened_links_val = 0;

	if (!game)
		return ERROR;

	for (i = 0; i < MAX_SPACES && space_get_id(game->spaces[i]) != -1; i++)
	{
		opened_links_val = 0;

		space = game->spaces[i];

		north = game_get_link(game, space_get_north(space));
		east = game_get_link(game, space_get_north(space));
		south = game_get_link(game, space_get_north(space));
		west = game_get_link(game, space_get_north(space));

		if (link_getStatus(north) == OPENED)
			opened_links_val += 1;
		if (link_getStatus(east) == OPENED)
			opened_links_val += 2;
		if (link_getStatus(south) == OPENED)
			opened_links_val += 4;
		if (link_getStatus(west) == OPENED)
			opened_links_val += 8;

		light = space_get_light(space);

		printf("Space id[%ld] i[%d]\n", space_get_id(space), i);
		printf("\tLight is (0 false)-> %d\n", light);
		printf("\tCurrent sprite    -> %d\n\n", opened_links_val);

		if (light == FALSE)
			space_setCurrentSprite(space, 16);
		else
			space_setCurrentSprite(space, opened_links_val);
	}

	return OK;
}

BOOL game_is_over(Game *game)
{
	return FALSE;
}

/* ===========================================================================================================*/
/* ================================================CALLBACKS==================================================*/
/* ===========================================================================================================*/

void game_callback_unknown(Game *game)
{
}

void game_callback_exit(Game *game)
{
}

void game_callback_pickup(Game *game)
{
	/* TODO : check if the object exists (same for drop) */
	int i = 0;
	Id debug = 0;

	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space *space_pointer = game_get_space(game, player_locId);
	char object[20] = {0};

	strcpy(object, command_get_id(game->last_cmd));
	object_id = object_get_id(game_get_object(game, object));

	if (!game)
		return;
	if (game_get_object_location(game, object_id) == game_get_player_location(game))
	{
		player_setObjId(game->player, object_id);
		space_remove_object(space_pointer, object_id);
	}

	/* DEBUG : this is to check if it works (spoiler alert: it does)*/
	printf("ThiS niBBa has the following objects:\n");
	for (i = 1; debug != NO_ID && i < 10; i++)
	{
		debug = player_getObjId(game->player, i);
		printf("\tTHIS ONE -> %ld [%d]\n", debug, i);
	}

	return;
}

void game_callback_drop(Game *game)
{
	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space *space_pointer = game_get_space(game, player_locId);
	char object[20] = {0};

	if (!game)
		return;

	strcpy(object, command_get_id(game->last_cmd));
	object_id = object_get_id(game_get_object(game, object));

	if (object_id > MAX_OBJECTS)
		return;

	space_add_object(space_pointer, object_id);
	player_removeObjId(game->player, object_id);

	return;
}

void game_callback_roll(Game *game)
{
	die_roll(game->die);
	die_print(stdout, game->die);
	return;
}

void game_callback_move(Game *game)
{
	Link *link;

	Id link_id = NO_ID;
	Id next_space_id = NO_ID;
	Id act_space_id = NO_ID;
	char direction[20] = {0};

	if (!game)
		return;

	act_space_id = game_get_player_location(game);
	strcpy(direction, command_get_id(game->last_cmd));

	printf("Someone is trying to move...\n\tPlayer loc -> %ld\n\tMovement -> %s\n", act_space_id, direction);

	if (!game || act_space_id == NO_ID)
		return;

	if (strcmp(direction, "north") == 0)
		link_id = space_get_north(game_get_space(game, act_space_id));

	else if (strcmp(direction, "east") == 0)
		link_id = space_get_east(game_get_space(game, act_space_id));

	else if (strcmp(direction, "south") == 0)
		link_id = space_get_south(game_get_space(game, act_space_id));

	else if (strcmp(direction, "west") == 0)
		link_id = space_get_west(game_get_space(game, act_space_id));

	else
		return;

	link = game_get_link(game, link_id);

	if (link_getStatus(link) == CLOSED)
	{
		command_set_id(game->last_cmd, "thats closed");
		return;
	}

	next_space_id = link_getSpace2(link);

	printf("Id of link you are trying to use -> %ld\n", link_id);
	printf("\tId of actposition -> %ld\n", link_getSpace1(link));
	printf("\tId of destination -> %ld\n", link_getSpace2(link));

	if (next_space_id != NO_ID)
		game_set_player_location(game, next_space_id);

	printf("Player's new location -> %ld\n", game_get_player_location(game));
}

void game_callback_check(Game *game)
{
	char object_description[20] = {0};
	char space_description[20] = {0};

	Space *current_space = game_get_space(game, player_getLocId(game->player));
	Object *object = NULL;

	if (!game || !current_space)
		return;

	/* If you are checking your space */
	if (strcasecmp(command_get_id(game->last_cmd), "s") == 0 || strcasecmp(command_get_id(game->last_cmd), "space") == 0)
	{
		if (space_get_light(current_space) == TRUE)
			strcpy(space_description, space_get_description(current_space));
		else
			strcpy(space_description, "you can't see");

		printf("Description -> %s\n", space_description);

		command_set_id(game->last_cmd, space_description);
	}
	/* If you are checking an object */
	else
	{
		object = game_get_object(game, command_get_id(game->last_cmd));

		if (object)
		{
			if (object_get_moved(object) == FALSE)
				strcpy(object_description, object_get_description(object));
			else
				strcpy(object_description, object_get_description_alternative(object));
		}
		else
		{
			strcpy(object_description, "no object with that name bruh");
		}

		command_set_id(game->last_cmd, object_description);
	}

	return;
}

void game_callback_turnOn(Game *game)
{
	char object_name[20] = {0};

	Object *object = NULL;

	if (!game)
		return;

	strcpy(object_name, command_get_id(game_get_last_command(game)));

	object = game_get_object(game, object_name);

	object_set_ilumnati(object, TRUE);
}

void game_callback_turnOff(Game *game)
{
	char object_name[20] = {0};

	Object *object = NULL;

	if (!game)
		return;

	strcpy(object_name, command_get_id(game_get_last_command(game)));

	object = game_get_object(game, object_name);

	object_set_ilumnati(object, FALSE);
}

void game_callback_open(Game *game)
{
	char packed_string[20] = {0};
	char unpak_link[20] = {0};
	char unpak_object[20] = {0};

	Link *link = NULL;
	Id link_id = NO_ID;
	Id actpos = NO_ID;

	if (!game)
		return;

	/* Unpacking with strtok */
	strcpy(packed_string, command_get_id(game_get_last_command(game)));
	strcpy(unpak_link, strtok(packed_string, "/"));
	strcpy(unpak_object, strtok(NULL, "/"));

	printf("Unpak -> [%s] - [%s]", unpak_link, unpak_object);

	actpos = game_get_player_location(game);

	if (strcasecmp(unpak_link, "n") == 0 || strcasecmp(unpak_link, "north") == 0)
		link_id = space_get_north(game_get_space(game, actpos));

	else if (strcasecmp(unpak_link, "e") == 0 || strcasecmp(unpak_link, "east") == 0)
		link_id = space_get_east(game_get_space(game, actpos));

	else if (strcasecmp(unpak_link, "s") == 0 || strcasecmp(unpak_link, "south") == 0)
		link_id = space_get_south(game_get_space(game, actpos));

	else if (strcasecmp(unpak_link, "w") == 0 || strcasecmp(unpak_link, "west") == 0)
		link_id = space_get_west(game_get_space(game, actpos));

	else
		return;

	link = game_get_link(game, link_id);

	printf("Next move should be -> %ld\n", link_getSpace2(link));
	printf("Currently has STATUS -> %d\n", link_getStatus(link));

	link_setStatus(link, OPENED);

	printf("Currently has STATUS -> %d\n", link_getStatus(link));
}