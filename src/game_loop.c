#include <stdio.h>
#include <stdlib.h>

#include "../include/graphic_engine.h"

int main(int argc, char *argv[])
{
	Game * game = NULL;

	FILE * log;
	char log_dir[1024] = "./log/";

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
		printf("Saving session on log\n");
		log = fopen(strcat(log_dir,argv[3]), "w+");
	}

	/* load */
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
/* Falta que ponga OK o no y que ponga el nombre del propio cmmand */
			
			fprintf(log, "%d %s\n", command_getCmd(command), command_get_id(command)); 
		}
	}

	fclose(log);
	command_free(command);
	game_destroy(game);
	graphic_engine_destroy(gengine);

	return 0;
}
