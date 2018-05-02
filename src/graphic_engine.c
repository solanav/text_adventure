/**
 * @brief Uses screen.* to create the UI
 *
 * @file graphic_engine.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/screen.h"
#include "../include/graphic_engine.h"
#include "../include/set.h"

#define STD_SPACE "             "
#define STD_SPACE1 "    "

/*This is the definition of graphic engine for the object functions*/
struct _Graphic_engine
{
	Area *map;      /*!< Mapa, dibujo*/
	Area *descript; /*!< donde van las descripciones*/
	Area *banner;   /*!< banner*/
	Area *help;     /*!<  ayuda*/
	Area *feedback; /*!< Commandos realizados e info*/
};

Graphic_engine *graphic_engine_create()
{
	static Graphic_engine *ge = NULL;

	if (ge)
		return ge;

	screen_init();
	ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));

	ge->map = screen_area_init(1, 1, 38, 16);
	ge->descript = screen_area_init(40, 1, 34, 16);
	ge->banner = screen_area_init(1, 18, 23, 1);
	ge->help = screen_area_init(1, 19, 73, 3);
	ge->feedback = screen_area_init(1, 23, 73, 5);

	return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
	if (!ge)
		return;

	screen_area_destroy(ge->map);
	screen_area_destroy(ge->descript);
	screen_area_destroy(ge->banner);
	screen_area_destroy(ge->help);
	screen_area_destroy(ge->feedback);

	screen_destroy();
	free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
	int i;
	Id id_act = NO_ID, spriteId = NO_ID;

	char str[255] = {0};

	F_Command *last_cmd = NULL;
	T_Command last_cmd_text = UNKNOWN;

	extern char *cmd_to_str[];

	Space *space_act = NULL;
	Sprite *sprite = NULL;
	Object *object = NULL;
	Player *player = NULL;

	/* Paint the in the map area */
	screen_area_clear(ge->map);
	if ((id_act = game_get_player_location(game)) != NO_ID)
	{
		space_act = game_get_space(game, id_act);
		spriteId = space_getSprite(space_act, space_getCurentSprite(space_act));
		sprite = game_get_sprite(game, spriteId);

		if (!sprite)
		{
			printf("ERROR, COULDN'T FIND SPRITE\n");
			exit(0);
		}

		for (i = 0; i < 16; i++)
		{
			sprintf(str, "%s", sprite_getData(sprite, i));
			screen_area_puts(ge->map, str);
		}
	}

	/* Paint the in the description area */
	screen_area_clear(ge->descript);

	print_new_line(ge->descript, 1);
	sprintf(str, " You see:");
	screen_area_puts(ge->descript, str);

	print_new_line(ge->descript, 1);

	for (i=0; i<MAX_OBJECTS; i++)
	{
		object = game_get_object_from_id(game, set_get_id(space_get_objects_id(space_act), i));

		if (object_get_name(object))
		{
			if (object_get_iluminati(object) == FALSE)
				sprintf(str, "      - %s", object_get_name(object));
			else
			{
				if(object_get_on(object) == TRUE)
					sprintf(str, "      - %s [ON]", object_get_name(object));
				else
					sprintf(str, "      - %s [OFF]", object_get_name(object));
			}
			screen_area_puts(ge->descript, str);
		}
	}

	print_new_line(ge->descript, 1);
	sprintf(str, " Inventory:");
	screen_area_puts(ge->descript, str);
	
	player = game_get_player(game);

	for (i=0; i<MAX_INV_SIZE; i++)
	{
		object = game_get_object_from_id(game, player_getObjId(player, i));
		
		if (object_get_name(object))
		{
			printf("PLAYER OBJECT [%d]->[%s]\n", i, object_get_name(object));
			if (object_get_iluminati(object) == FALSE)
				sprintf(str, "      - %s", object_get_name(object));
			else
			{
				if(object_get_on(object) == TRUE)
					sprintf(str, "      - %s [ON]", object_get_name(object));
				else
					sprintf(str, "      - %s [OFF]", object_get_name(object));
			}
			screen_area_puts(ge->descript, str);
		}
	}

	/*
	print_new_line(ge->descript, 1);
	sprintf(str, " Last roll stored value: %d", game_get_last_roll(game));
	screen_area_puts(ge->descript, str);
	*/

	/* Banner */
	screen_area_puts(ge->banner, " The game of the Goose ");

	/* Help */
	screen_area_clear(ge->help);
	sprintf(str, " The commands you can use are:");
	screen_area_puts(ge->help, str);
	sprintf(str, " Move or m <North (n), East (e), South (s), West (w)>");
	screen_area_puts(ge->help, str);
	sprintf(str, " Pickup or u <Id>, Drop or d <Id>, Exit or e");
	screen_area_puts(ge->help, str);

	/* Command History */
	last_cmd_text = game_get_last_command_text(game);
	last_cmd = game_get_last_command(game);
	sprintf(str, " %s > %s", cmd_to_str[last_cmd_text - NO_CMD], command_get_id(last_cmd));
	screen_area_puts(ge->feedback, str);

	if (last_cmd_text == ROLL)
	{
		sprintf(str, "   You rolled: %d", game_get_last_roll(game));
		screen_area_puts(ge->feedback, str);
	}

	command_set_id(game_get_last_command(game), "");

	/* Input */
	screen_paint();
	printf("prompt:> ");
}

char *create_objects_string(Game *game, Id id)
{
	int i, j;
	char *obj = (char *)calloc(20, sizeof(char *));

	for (i = 1, j = 0; i < 5; i++)
	{
		if (game_get_object_location(game, i) == id)
		{
			obj[j] = 'o';
			obj[j + 1] = 48 + i;
			j = j + 2;
		}
		else
		{
			obj[j] = ' ';
			obj[j + 1] = ' ';
			j = j + 2;
		}
	}

	return obj;
}

void print_new_line(Area *area, int number)
{
	int i;
	char str[255] = "\0";

	for (i = 0; i < number; i++)
	{
		sprintf(str, " ");
		screen_area_puts(area, str);
	}
}
