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
	Area * map; /*!< Mapa, dibujo*/
	Area * descript; /*!< donde van las descripciones*/
	Area * banner; /*!< banner*/
	Area * help; /*!<  ayuda*/
	Area * feedback; /*!< Commandos realizados e info*/
};

Graphic_engine *graphic_engine_create()
{
	static Graphic_engine *ge = NULL;

	if (ge) return ge;

	screen_init();
	ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

	ge->map      = screen_area_init( 1, 1, 48, 20);
	ge->descript = screen_area_init(50, 1, 34, 20);
	ge->banner   = screen_area_init(28,22, 23,  1);
	ge->help     = screen_area_init( 1,23, 83,  3);
	ge->feedback = screen_area_init( 1,27, 83,  5);

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
	int i, j;
	Id id_act = NO_ID, obj_loc = NO_ID;
	char ply[20]="\0";
	char str[255];
	F_Command* last_cmd = NULL;
	T_Command last_cmd_text = UNKNOWN;
	extern char *cmd_to_str[];

	/* Paint the in the map area */
	screen_area_clear(ge->map);
	if ((id_act = game_get_player_location(game)) != NO_ID)
	{
		print_new_line(ge->map, 1);
		graphic_engine_paint_space(ge, game, 0);
		print_new_line(ge->map, 1);
		graphic_engine_paint_space(ge, game, 1);
		print_new_line(ge->map, 1);
		graphic_engine_paint_space(ge, game, 2);
	}

	/* Paint the in the description area */
	screen_area_clear(ge->descript);

	print_new_line(ge->descript, 1);
	sprintf(str, " Game objects:");
	screen_area_puts(ge->descript, str);

	print_new_line(ge->descript, 1);
	for(i=1; i<5; i++)
	{
		if ((obj_loc = game_get_object_location(game, i)) != NO_ID)
		{
			sprintf(str, "  Object o%d [%s] location:%d", i, object_get_name(game_get_object_from_id(game, i)), (int)obj_loc);
			screen_area_puts(ge->descript, str);
		}
	}

	print_new_line(ge->descript, 1);
	for(i=1, j=0; i<5; i++)
	{
		if(game_get_object_location(game, i) == NO_ID)
		{
			ply[j]='o';
			ply[j+1] = 48+i;
			ply[j+2] = ',';
			ply[j+3] = ' ';
			j = j + 4;
		}
		else
		{
			ply[j]=' ';
			ply[j+1]=' ';
		}
	}

	print_new_line(ge->descript, 1);
	sprintf(str, " Player objects: %s", ply);
	screen_area_puts(ge->descript, str);

	print_new_line(ge->descript, 1);
	sprintf(str, " Last roll stored value: %d", game_get_last_roll(game));
	screen_area_puts(ge->descript, str);

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
	sprintf(str, " %s > %s", cmd_to_str[last_cmd_text-NO_CMD], command_get_id(last_cmd));
	screen_area_puts(ge->feedback, str);

	if(last_cmd_text == ROLL)
	{
		sprintf(str, "   You rolled: %d", game_get_last_roll(game));
		screen_area_puts(ge->feedback, str);
	}

	command_set_id(game_get_last_command(game), "");

	/* Input */
	screen_paint();
	printf("prompt:> ");
}

void graphic_engine_paint_space(Graphic_engine *ge, Game *game, int position_of_space)
{
	char * gdesc[3];
	char * obj_string_back;
	char * obj_string_act;
	char * obj_string_next;
	char * obj;
	char str[255];
	char hero[3] = "8D";
	char no_string[20] = "                 ";
	char link_left[3] = {0};
	char link_right[3] = {0};
	char link_id_left_char[4] = {0};
	char link_id_right_char[4] = {0};

	Id id_act = NO_ID;
	Id id_back = NO_ID;
	Id id_next = NO_ID;
	Id id_left = NO_ID;
	Id id_right = NO_ID;
	Id id_to_print = NO_ID;
	Id link_id_back, link_id_next, link_id_left, link_id_right;

	Space * space_act = NULL;
	Space * space_last = NULL;
	Space * space_next = NULL;
	Space * space_to_use = NULL;

	/* Get useful data */
	id_act = game_get_player_location(game);

	space_act = game_get_space(game, id_act);

	link_id_back = space_get_north(space_act);
	link_id_next = space_get_south(space_act);
	link_id_left = space_get_west(space_act);
	link_id_right = space_get_east(space_act);

	id_back = link_getSpace1(game_get_link(game, link_id_back));
	id_next = link_getSpace2(game_get_link(game, link_id_next));
	id_left = link_getSpace1(game_get_link(game, link_id_left));
	id_right = link_getSpace2(game_get_link(game, link_id_right));

	space_last = game_get_space(game, id_back);
	space_next = game_get_space(game, id_next);

	/* Check gdesc and put it to spaces if there is none */
	if (position_of_space == 0) space_to_use = space_last;
	if (position_of_space == 1) space_to_use = space_act;
	if (position_of_space == 2) space_to_use = space_next;

	gdesc[0] = space_get_gdesc_0(space_to_use);
	gdesc[1] = space_get_gdesc_1(space_to_use);
	gdesc[2] = space_get_gdesc_2(space_to_use);

	if (gdesc[0] == NULL) gdesc[0] = no_string;
	if (gdesc[1] == NULL) gdesc[1] = no_string;
	if (gdesc[2] == NULL) gdesc[2] = no_string;

	/* Get objects of space and dump them into strings */
	obj_string_back = create_objects_string(game, id_back);
	obj_string_act = create_objects_string(game, id_act);
	obj_string_next = create_objects_string(game, id_next);

	if (position_of_space == 0) obj = obj_string_back;
	else if (position_of_space == 1) obj = obj_string_act;
	else if (position_of_space == 2) obj = obj_string_next;

	/* Set hero to spaces or to the hero string */
	if (position_of_space != 1) strcpy(hero, "  ");

	/* Select what id you have to print */
	if (position_of_space == 0) id_to_print = id_back;
	if (position_of_space == 1) id_to_print = id_act;
	if (position_of_space == 2) id_to_print = id_next;

	/* Links to left and right */
	if(id_left > 10) sprintf(link_left, "%ld<", id_left);
	else if(id_left == -1) sprintf(link_left, "   ");
	else sprintf(link_left, "%ld <", id_left);

	if(id_right > 10) sprintf(link_right, ">%ld", id_right);
	else if(id_right == -1) sprintf(link_right, "   ");
	else sprintf(link_right, "> %ld", id_right);

	if(link_id_left > 10) sprintf(link_id_left_char, "[%ld]", link_id_left);
	else if(link_id_left == -1) sprintf(link_id_left_char, "    ");
	else sprintf(link_id_left_char, "[%ld ]", link_id_left);

	if(link_id_right > 10) sprintf(link_id_right_char, "[%ld]", link_id_right);
	else if(link_id_right == -1) sprintf(link_id_right_char, "    ");
	else sprintf(link_id_right_char, "[ %ld]", link_id_right);

	/* Print space */
	if (id_to_print != -1)
	{
		if (position_of_space != 0)
		{
			sprintf(str, "%s+-------------------+", STD_SPACE);
			screen_area_puts(ge->map, str);
			sprintf(str, "%s| %s                |", STD_SPACE, hero);
			screen_area_puts(ge->map, str);
		}

		sprintf(str, "%s|%s%2d|", STD_SPACE, gdesc[0], (int) id_to_print);
		screen_area_puts(ge->map, str);

		if (position_of_space == 1)
		{
			sprintf(str, "%s%s %s | %s | %s %s", STD_SPACE1, link_id_left_char, link_left, gdesc[1], link_right, link_id_right_char);
			screen_area_puts(ge->map, str);
		}
		else
		{
			sprintf(str, "%s| %s |", STD_SPACE, gdesc[1]);
			screen_area_puts(ge->map, str);
		}

		sprintf(str, "%s| %s |", STD_SPACE, gdesc[2]);
		screen_area_puts(ge->map, str);
		sprintf(str, "%s|           %s|", STD_SPACE, obj);
		screen_area_puts(ge->map, str);

		if (position_of_space != 2)
		{
			sprintf(str, "%s+-------------------+", STD_SPACE);
			screen_area_puts(ge->map, str);
		}
	}
	else
	{
		if (position_of_space == 0) print_new_line(ge->map, 5);
		if (position_of_space == 2) print_new_line(ge->map, 6);
	}

	free(obj_string_back);
	free(obj_string_act);
	free(obj_string_next);
}

char * create_objects_string(Game * game, Id id)
{
	int i, j;
	char * obj = (char *) calloc(20, sizeof(char *));

	for (i=1, j=0; i<5; i++)
	{
		if(game_get_object_location(game, i) == id)
		{
			obj[j]='o';
			obj[j+1]= 48+i;
			j=j+2;
		}
		else
		{
			obj[j]=' ';
			obj[j+1]=' ';
			j=j+2;
		}
	}

	return obj;
}

void print_new_line(Area * area, int number)
{
	int i;
	char str[255] = "\0";

	for (i = 0; i < number; i++)
	{
		sprintf(str, " ");
		screen_area_puts(area, str);
	}
}
