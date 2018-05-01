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
			if (i == 6)
			{
				line[16] = ' ';
				line[17] = ',';
				line[18] = ',';
				line[19] = ',';
				line[20] = ' ';
				sprite_putLine(sprite, line, i);
				i++;
			}
			else if (i == 7)
			{
				line[16] = '(';
				line[17] = 'o';
				line[18] = '_';
				line[19] = 'o';
				line[20] = ')';
				sprite_putLine(sprite, line, i);
				i++;
			}
			else if (i == 8)
			{
				line[16] = '<';
				line[17] = '|';
				line[18] = ' ';
				line[19] = '|';
				line[20] = 92;
				sprite_putLine(sprite, line, i);
				i++;
			}
			else if (i == 9)
			{
				line[16] = ' ';
				line[17] = '/';
				line[18] = ' ';
				line[19] = 92;
				line[20] = ' ';
				sprite_putLine(sprite, line, i);
				i++;
			}
			else
			{
				sprite_putLine(sprite, line, i);
				i++;
			}
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
}
