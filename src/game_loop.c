/**
 * @brief Main loop
 *
 * @file game_loop.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/graphic_engine.h"

int main(int argc, char *argv[])
{
	Game * game = NULL;

	FILE * log = NULL;
	char log_dir[1024] = "log/";
	char *cmd_to_str[8] = {"No command", "Unknown", "Exit", "Pickup", "Drop", "Roll", "Move", "Check"};

	F_Command * command  = command_create();
	Graphic_engine *gengine;

	/* Create game */
	game = game_create();
	if (!game)
	{
		printf("Couldn't create game\n");
		return 1;
	}

	if (argc < 2 || argc == 3)
	{
		fprintf(stderr, "Use: %s\t<game_data_file>\n\t\t\t-l <log_file_name>\n\n", argv[0]);
		return 1;
	}

	if (argc == 4 && strcmp(argv[2], "-l")==0)
	{
		log = fopen(strcat(log_dir,argv[3]), "w+");
	}

	/* load data.dat */
	if (game_create_from_file(game, argv[1]) == ERROR)
	{
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}

	/* start graphic engine */
	if ((gengine = graphic_engine_create()) == NULL)
	{
		fprintf(stderr, "Error while initializing graphic engine.\n");
		game_destroy(game);
		return 1;
	}

	/* main loop */
	while ((command_getCmd(command) != EXIT) && !game_is_over(game))
	{
		graphic_engine_paint_game(gengine, game);

		if(get_user_input(command)== OK)
			game_update(game, command);

		if (argc == 4 && strcmp(argv[2], "-l")==0)
		{
			fprintf(log, "%s %s\n", cmd_to_str[game_get_last_command_text(game, 0)+1], command_get_id(game_get_last_command(game, 0))); 
		}
	}

	if (log != NULL) fclose(log);
	command_free(command);
	game_destroy(game);
	graphic_engine_destroy(gengine);

	return 0;
}
