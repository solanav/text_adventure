/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Antonio Solana
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
#define PLAYER_ID 1
#define DIE_SEED 666
#define STARTING_SPACE 25
#define NO_LIGHT_SPRITE 16
#define MOVES_TO_START_RULES 1000
#define FURNANCE_ID 21

struct _Game
{
	Player *player;		       /*!< Jugador*/
	Object *objects[MAX_OBJECTS];  /*!< Array de objetos*/
	Space *spaces[MAX_SPACES + 1]; /*!< Array de espacios*/
	Link *links[MAX_LINK];	 /*!< Array de links*/
	Die *die;		       /*!< Dado */
	F_Command *last_cmd[2];	   /*!< ultimos comandos*/
	Sprite *sprites[MAX_SPRITES];  /*!< sprites del mapa*/
	Rule_Data *rule_data;	  /*!< datos para su uso en game_rules*/
};

typedef void (*callback_fn)(Game *game);

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
		return NULL;

	for (i = 0; i < MAX_SPACES; i++)
	{
		game->spaces[i] = NULL;
	}

	for (i = 0; i < MAX_LINK; i++)
	{
		game->links[i] = NULL;
	}

	for (i = 0; i < MAX_SPRITES; i++)
	{
		game->sprites[i] = NULL;
	}

	game->die = die_ini(DIE_SEED);
	game_set_player_location(game, NO_ID);

	game->last_cmd[0] = NULL;
	game->last_cmd[1] = NULL;

	game->player = player_create("player1", NO_ID, NO_ID, PLAYER_ID);
	game->rule_data = rules_create();

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

	/* Put each link in the corresponding space */
	for (i = 0; i < MAX_LINK; i++)
	{
		link_id = link_getId(game->links[i]);

		if (link_id == NO_ID)
			continue;

		space_act_id = link_getSpace1(game->links[i]);

		space_act = game_get_space(game, space_act_id);

		direction = link_getDirection(game_get_link(game, link_id));

		if (direction == NORTH)
			space_set_north(space_act, link_id);
		else if (direction == EAST)
			space_set_east(space_act, link_id);
		else if (direction == SOUTH)
			space_set_south(space_act, link_id);
		else if (direction == WEST)
			space_set_west(space_act, link_id);
	}

	game_set_player_location(game, (long int)STARTING_SPACE);

	update_sprites(game);

	return OK;
}

STATUS game_destroy(Game *game)
{
	int i = 0;

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
	rules_destroy(game->rule_data);
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

Die *game_get_die(Game *game)
{
	if (!game)
		return NULL;

	return game->die;
}

Object *game_get_object(Game *game, char *object_name)
{
	int i;

	if (!game || !object_name)
		return NULL;

	for (i = 0; i < MAX_OBJECTS && game->objects[i]; i++)
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

	for (i = 0; i < MAX_OBJECTS; i++)
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
	if (!game || pos == NO_ID)
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
				return space_get_id(game->spaces[i]);
			}
		}
	}
	return NO_ID;
}

STATUS game_update(Game *game, F_Command *cmd)
{
	if (!game || !cmd)
		return ERROR;

	game->last_cmd[1] = game->last_cmd[0];
	game->last_cmd[0] = cmd;

	(*game_callback_fn_list[command_getCmd(cmd)])(game);

	update_rules(game, game->rule_data);
	update_sprites(game);

	return OK;
}

F_Command *game_get_last_command(Game *game, int i)
{
	return game->last_cmd[i];
}

T_Command game_get_last_command_text(Game *game, int i)
{
	return command_getCmd(game->last_cmd[i]);
}

char * game_get_last_command_parameters(Game* game, int i)
{
	return command_get_id(game->last_cmd[i]);
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

STATUS game_add_object(Game *game, Object *object)
{
	int i = 0;

	if (object == NULL)
		return ERROR;

	while ((i < MAX_OBJECTS) && (game->objects[i] != NULL))
		i++;

	if (i >= MAX_OBJECTS)
		return ERROR;

	game->objects[i] = object;

	return OK;
}

Sprite *game_get_sprite(Game *game, Id id)
{
	int i;

	if (!game || id == NO_ID)
		return NULL;

	for (i = 0; i < MAX_SPRITES; i++)
	{
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

STATUS game_set_link(Game *game, Id link_id, Id space_id0, Id space_id1, int direction, LinkStatus door)
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
			link_setId(game->links[i], link_id);
			link_setSpaces(game->links[i], space_id0, space_id1);
			link_setDirection(game->links[i], direction);
			link_setStatus(game->links[i], door);

			printf("Saving link %d with door %d\n", i, door);
			link_print(game->links[i]);

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

	BOOL player_light = FALSE;
	Space *space = NULL;
	Player *player = NULL;
	Object *object = NULL;

	int opened_links_val = 0;

	if (!game)
		return ERROR;

	space = game_get_space(game, game_get_player_location(game));

	player = game_get_player(game);
	for (i = 0; i < MAX_INV_SIZE; i++)
	{
		object = game_get_object_from_id(game, player_getObjId(player, i));
		if (object_get_name(object))
		{
			if (object_get_on(object) == TRUE)
			{
				player_light = TRUE;
				i = MAX_INV_SIZE;
			}
		}
	}

	if (space_get_light(space) == FALSE)
	{
		if (player_light == FALSE)
			space_setCurrentSprite(space, NO_LIGHT_SPRITE);
		else
			space_setCurrentSprite(space, opened_links_val);
	}
	else
	{
		space_setCurrentSprite(space, opened_links_val);
	}

	/* If space 62 (cave entrance) has its door open, change sprite to the open door one */
	if (link_getStatus(game_get_link(game, space_get_south(game_get_space(game, 62)))) == OPENED)
	{
		space_setCurrentSprite(game_get_space(game, 62), 1);
	}

	return OK;
}

STATUS update_rules(Game *game, Rule_Data *rule_data)
{
	Player *player = NULL;
	Die *die = NULL;
	Space *space = NULL;
	Inventory *inventory = NULL;

	BOOL key1 = FALSE, key2 = FALSE, key3 = FALSE, key4 = FALSE, key5 = FALSE;

	if (!game || !rule_data)
		return ERROR;

	player = game_get_player(game);
	die = game_get_die(game);
	space = game_get_space(game, game_get_player_location(game));
	inventory = player_getInventory(player);

	die_roll(die);
	rules_setDieVal(rule_data, die_get_last_roll(die));

	if (game_get_last_command_text(game, 0) == MOVE)
		rules_setMoveCount(rule_data, rules_getMoveCount(rule_data) + 1);

	if (rules_getMoveCount(rule_data) >= MOVES_TO_START_RULES)
	{
		printf("RULE -> %d\n", rules_getDieVal(rule_data));
		player_setTreeState(player, FALSE);

		if (rules_getDieVal(rule_data) == NO_RULES)
		{
			/* NO RULE */
		}
		else if (rules_getDieVal(rule_data) == NO_LIGHT)
		{
			space_set_light(space, FALSE);
		}
		else if (rules_getDieVal(rule_data) == GO_START)
		{
			game_set_player_location(game, STARTING_SPACE);
		}
		else if (rules_getDieVal(rule_data) == NO_TORCH)
		{
			player_removeObjId(player, OBJID_TORCH);
		}
		else if (rules_getDieVal(rule_data) == BECOME_TREE)
		{
			player_setTreeState(player, TRUE);
		}
		else if (rules_getDieVal(rule_data) == GO_RAND)
		{
			player_setLocId(player, die_getRandomNumber(die));
		}
		else /* execute GIVE_OBJ */
		{
			player_setObjId(player, die_getRandomNumber(die));
		}

		rules_setMoveCount(rule_data, 0);
	}

	if (game_get_player_location(game) == FURNANCE_ID)
	{
		if (inventory_checkById(inventory, OBJID_KEY1) == TRUE)
			key1 = TRUE;
		if (inventory_checkById(inventory, OBJID_KEY2) == TRUE)
			key2 = TRUE;
		if (inventory_checkById(inventory, OBJID_KEY3) == TRUE)
			key3 = TRUE;
		if (inventory_checkById(inventory, OBJID_KEY4) == TRUE)
			key4 = TRUE;
		if (inventory_checkById(inventory, OBJID_KEY5) == TRUE)
			key5 = TRUE;

		if (key1 == TRUE && key2 == TRUE && key3 == TRUE && key4 == TRUE && key5 == TRUE)
		{
			player_removeObjId(player, OBJID_KEY1);
			player_removeObjId(player, OBJID_KEY2);
			player_removeObjId(player, OBJID_KEY3);
			player_removeObjId(player, OBJID_KEY4);
			player_removeObjId(player, OBJID_KEY5);

			player_setObjId(player, OBJID_MASTERKEY);
		}
			
	}

	return OK;
}

BOOL game_is_over(Game *game)
{
	return FALSE;
}

void game_callback_unknown(Game *game)
{
}

void game_callback_exit(Game *game)
{
}

void game_callback_pickup(Game *game)
{
	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space *space_pointer = game_get_space(game, player_locId);
	char object[MAX_STRING] = {0};

	strcpy(object, command_get_id(game->last_cmd[0]));
	object_id = object_get_id(game_get_object(game, object));

	if (!game)
		return;

	if (game_get_object_location(game, object_id) == game_get_player_location(game))
	{
		if (object_get_mobile(game_get_object_from_id(game, object_id)) == TRUE)
		{
			sprintf(object, "%sOK", object);
			player_setObjId(game->player, object_id);
			space_remove_object(space_pointer, object_id);
		}
		else
		{
			command_set_id(game_get_last_command(game, 0), "you can't move that");
		}
	}

	return;
}

void game_callback_drop(Game *game)
{
	Id player_locId = game_get_player_location(game);
	Id object_id = NO_ID;
	Space *space_pointer = game_get_space(game, player_locId);
	char object[MAX_STRING] = {0};

	if (!game)
		return;

	strcpy(object, command_get_id(game->last_cmd[0]));
	object_id = object_get_id(game_get_object(game, object));

	if (object_id > MAX_OBJECTS)
		return;

	if(player_removeObjId(game->player, object_id) == OK)
	{
		command_set_id(game->last_cmd[0], object);
		space_add_object(space_pointer, object_id);
	}
	else
	{
		command_set_id(game->last_cmd[0], "no");
	}

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
	char direction[MAX_STRING] = {0};

	Player *player = game_get_player(game);

	if (!game)
		return;

	act_space_id = game_get_player_location(game);
	strcpy(direction, command_get_id(game->last_cmd[0]));

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

	if(!link)
		command_set_id(game->last_cmd[0], "no");
	else
		command_set_id(game->last_cmd[0], direction);

	if (link_getStatus(link) == CLOSED)
	{
		command_set_id(game->last_cmd[0], "thats closed");
		return;
	}

	next_space_id = link_getSpace2(link);

	if (player_getTreeState(player) == TRUE)
		command_set_id(game->last_cmd[0], "you are a tree :^)");
	else if (next_space_id != NO_ID)
		game_set_player_location(game, next_space_id);
	else
		command_set_id(game->last_cmd[0], "you can't move there");
}

void game_callback_check(Game *game)
{
	char object_description[MAX_STRING] = {0};
	char space_description[MAX_STRING] = {0};

	Space *current_space = game_get_space(game, player_getLocId(game->player));
	Object *object = NULL;

	if (!game || !current_space)
		return;

	/* If you are checking your space */
	if (strcasecmp(command_get_id(game->last_cmd[0]), "s") == 0 || strcasecmp(command_get_id(game->last_cmd[0]), "space") == 0)
	{
		if (space_get_light(current_space) == TRUE)
			strcpy(space_description, space_get_description(current_space));
		else
			strcpy(space_description, "you can't see");

		printf("Description -> %s\n", space_description);

		command_set_id(game->last_cmd[0], space_description);
	}
	/* If you are checking an object */
	else
	{
		object = game_get_object(game, command_get_id(game->last_cmd[0]));

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

		command_set_id(game->last_cmd[0], object_description);
	}

	return;
}

void game_callback_turnOn(Game *game)
{
	char object_name[MAX_STRING] = {0};

	Object *object = NULL;

	if (!game)
		return;

	strcpy(object_name, command_get_id(game_get_last_command(game, 0)));

	object = game_get_object(game, object_name);

	if(object_set_on(object, TRUE) == ERROR)
		command_set_id(game->last_cmd[0], "no");
}

void game_callback_turnOff(Game *game)
{
	char object_name[MAX_STRING] = {0};

	Object *object = NULL;

	if (!game)
		return;

	strcpy(object_name, command_get_id(game_get_last_command(game, 0)));

	object = game_get_object(game, object_name);

	if(object_set_on(object, FALSE) == ERROR)
		command_set_id(game->last_cmd[0], "no");
}

void game_callback_open(Game *game)
{
	char packed_string[MAX_STRING] = {0};
	char unpak_link[MAX_STRING] = {0};
	char unpak_object[MAX_STRING] = {0};

	Link *link = NULL;
	Id link_id = NO_ID;
	Id actpos = NO_ID;

	if (!game)
		return;

	/* Unpacking with strtok */
	strcpy(packed_string, command_get_id(game_get_last_command(game, 0)));
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
	{
		return;
	}

	link = game_get_link(game, link_id);

	printf("Using link -> %ld\n", link_id);
	printf("Next move should be -> %ld\n", link_getSpace2(link));
	printf("Currently has STATUS b -> %d\n", link_getStatus(link));

	if (inventory_checkById(player_getInventory(game_get_player(game)), OBJID_MASTERKEY) == TRUE)
	{
		if (strcasecmp(unpak_object, "masterkey") == 0)
		{
			if(link_setStatus(link, OPENED) == ERROR)
			{
				command_set_id(game->last_cmd[0], "error");
			}
		}
		else
		{
			command_set_id(game->last_cmd[0], "error");
		}
	}
		
	printf("Currently has STATUS a -> %d\n", link_getStatus(link));
}
