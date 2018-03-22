/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "client.h"

int main(int argc, char *argv[])
{
	Game game;

	F_Command * command  = command_create(NO_CMD, NO_ID);
	Graphic_engine *gengine;

	int socket;
	char * str_to_int = NULL;

	if (argc < 4)
	{
		fprintf(stderr, "Use: %s <game_data_file> <server_ip> <server_port>\n", argv[0]);
		return 1;
	}

	/* load */
	if (game_create_from_file(&game, argv[1]) == ERROR)
	{
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}

	/* start graphic engine */
	if ((gengine = graphic_engine_create()) == NULL)
	{
		fprintf(stderr, "Error while initializing graphic engine.\n");
		game_destroy(&game);
		return 1;
	}
	
	/* check connection to server */
	if (connect_to_server((char *) argv[2], strtol(argv[3], &str_to_int, 10), &socket))
	{
		fprintf(stderr, "Error connecting to server");
	}

	/* main loop */
	while ((command_getCmd(command) != EXIT) && !game_is_over(&game))
	{
		graphic_engine_paint_game(gengine, &game);
		get_user_input(command);
		game_update(&game, command);
		/* Update your position with server TODO: do it with a pthread shithead*/
		custom_request(&socket, (int) game_get_player_location(&game));
	}
	
	/* Tell the server you are disconnecting */
	disconnect(&socket);
	command_free(command);
	game_destroy(&game);
	graphic_engine_destroy(gengine);

	return 0;
}
