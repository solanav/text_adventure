/**
 * @brief Reads the sprites from a file
 *
 * @file sprite_loader.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/sprite_loader.h"

STATUS sprite_loader_map(Game *game, char *filename)
{
	FILE *file = NULL;

	int i = 0;
	Id j = 0;

	Sprite *sprite = NULL;
	char line[1000];

	if (!game)
		return ERROR;

	file = fopen(filename, "r");
	if (file == NULL)
		return ERROR;

	sprite = sprite_create(j);
	if (!sprite)
		return ERROR;

	while (fgets(line, WORD_SIZE, file))
	{
		if (i <= 16 && strcmp(line, "\n"))
		{
			sprite_putLine(sprite, line, i);
			i++;
		}
		else
		{
			i = 0;
			game_add_sprite(game, sprite, j);
			
			/* Create another sprite */
			j++;
			sprite = sprite_create(j);
			if (!sprite)
				return ERROR;
		}
	}

	
	fclose(file);

	return OK;
	/*TODO: LIBERAR MEMORIA*/
}
