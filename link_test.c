#include <stdio.h>
#include "link.h"
#include "game.h"
#include "types.h"

int main(int argc, char const *argv[])
{
	Game game;
	Link * link_test;

	if(argc < 2)
	{
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}

	if(game_create_from_file(&game, argv[1]) == ERROR)
	{
		fprintf(stderr, "Could not initialize game\n");
		return 1;
	}

	link_test = link_create(2);
	if(!link_test) goto err0;

	if(set_linkId(link_test, 3) == ERROR)
	{
		fprintf(stderr, "Error when setting Id\n");
		goto err1;
	}

	if(set_spacesId(&game, link_test, 1, 2) == ERROR)
	{
		fprintf(stderr, "Error when setting correct space ids\n");
		goto err1;
	}

	if(set_spacesId(&game, link_test, 1, 15) == OK)
	{
		fprintf(stderr, "Error when setting incorrect space ids\n");
		goto err1;
	}

	if(set_linkStatus(link_test, OPEN) == ERROR)
	{
		fprintf(stderr, "Error when setting status");
		goto err1;
	}

	print_link(link_test);

	link_destroy(link_test);
	game_destroy(&game);
	return 0;

	err1:
	link_destroy(link_test);
	err0:
	game_destroy(&game);
	return 1;
}
