#include <stdio.h>
#include <stdlib.h>

#include "../hdr/graphic_engine.h"

int main(int argc, char *argv[])
{
	Game * game = NULL;

	F_Command * command  = command_create();
	Graphic_engine *gengine;

	/* Create game */
	game = game_create();
	if (!game)
	{
		printf("Couldn't create game\n");
		return 1;
	}

	if (argc < 2)
	{
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
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
		get_user_input(command);
		game_update(game, command);
	}

	command_free(command);
	game_destroy(game);
	graphic_engine_destroy(gengine);

	return 0;
}
